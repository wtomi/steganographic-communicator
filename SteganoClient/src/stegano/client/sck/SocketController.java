package stegano.client.sck;

import javafx.application.Platform;
import javafx.beans.property.ReadOnlyObjectWrapper;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.concurrent.ScheduledService;
import javafx.concurrent.Task;
import javafx.util.Duration;
import stegano.client.model.Contact;
import stegano.client.model.World;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;
import java.nio.ByteBuffer;
import java.nio.charset.StandardCharsets;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.atomic.AtomicBoolean;

/**
 * Created by tommy on 18.02.2017.
 */
public class SocketController {
    private static SocketController ourInstance = new SocketController();

    private Socket socket;
    private Object socketLock = new Object();
    private DataInputStream inStream;
    private DataOutputStream outStream;

    private final int SERVER_BUFFSIZE = 8192;
    private ByteBuffer buf = ByteBuffer.allocate(SERVER_BUFFSIZE);

    //messages' types
    private final int USER_AUTH = 1;
    //subtypes
    private final int USER_AUTH_SUCCESS = 1;
    private final int USER_AUTH_FAILURE = 2;
    //end subtypes
    private final int USER_RECV_CONNTACTS = 2;
    //subtypes
    private final int USER_RECV_CONTACTS_PART = 1;
    private final int USER_RECV_CONTACTS_ALL = 2;
    //end subtypes
    private final int USER_RECV_MSG = 3;
    //subtypes
    private final int USER_RECV_MSG_PART = 1;
    private final int USER_RECV_MSG_ALL = 2;
    //end subtypes

    private final int SERVER_AUTH_REQUEST = 1;
    private final int SERVER_CONTACTS_REQUEST = 2;


    AtomicBoolean running = new AtomicBoolean(false);
    AtomicBoolean waitingForContacts = new AtomicBoolean(false);

    private ReadOnlyObjectWrapper<ObservableList<Contact>> contacts = new ReadOnlyObjectWrapper<>(World.getInstance().getContacts());

    public static SocketController getInstance() {
        return ourInstance;
    }

    private SocketController() {
    }

    public boolean connect(String host, String hostPassword, int port, String clientName) {

        if (running.compareAndSet(false, true)) {
            Task task = new SocketTask(host, hostPassword, port, clientName);
            Thread t = new Thread(task);
            t.setDaemon(true);
            t.start();
            return true;
        } else
            return false;
    }

    private List<String> recvUsersNames(DataInputStream in) throws IOException {
        List<String> recvNames = null;
        try {
            int msg_subtype;
            recvNames = new ArrayList<>();
            do {
                msg_subtype = in.readByte();
                int len = in.readInt();
                if (len > 0) {
                    in.readFully(buf.array(), 0, len);
                    String string = new String(buf.array(), 0, len);
                    String names[] = string.split("\0");
                    for (String s :
                            names) {
                        recvNames.add(s);
                    }
                }
            } while (msg_subtype != USER_RECV_CONTACTS_ALL);
        } catch (IOException e) {
            throw e;
        } finally {
            waitingForContacts.set(false);
            return recvNames;
        }
    }

    private class SocketTask extends Task<Void> {

        private final String host;
        private final int port;
        private final String hostPassword;
        private final String clientName;

        public SocketTask(String host, String hostPassword, int port, String clientName) {
            this.host = host;
            this.port = port;
            this.hostPassword = hostPassword;
            this.clientName = clientName;
        }

        @Override
        protected Void call() throws Exception {

            ScheduledService<Void> ssvc = null;
            try {
                socket = new Socket(host, port);
                inStream = new DataInputStream(socket.getInputStream());
                outStream = new DataOutputStream(socket.getOutputStream());
                if (authenticate(inStream, outStream)) { //if authentication succeeded
                    ssvc = new ContactsRequestService();
                    ssvc.setPeriod(Duration.seconds(3));
                    //ssvc.setRestartOnFailure(true);
                    ssvc.start();
                    boolean out = false;
                    while (!out) {
                        byte msg_type = inStream.readByte();
                        switch (msg_type) {
                            case USER_RECV_CONNTACTS:
                                update_contacts(inStream);
                                break;
                            case USER_RECV_MSG:
                                break;
                            default:
                                throw new WrongMsgTypeException("Wrong message's type");
                        }
                    }
                }
            } catch (IOException e) {
                e.printStackTrace();
            } catch (TooLongMessageException e) {
                e.printStackTrace();
            } catch (WrongMsgTypeException e) {
                e.printStackTrace();
            } catch (Exception e) {
                e.printStackTrace();
            } finally {
                if (socket != null) {
                    socket.close();
                    socket = null;
                }
                if (inStream != null) {
                    inStream.close();
                    inStream = null;
                }
                if (outStream != null) {
                    outStream.close();
                    outStream = null;
                }
                running.set(false);
                ssvc.cancel();
            }
            return null;
        }

        private void update_contacts(DataInputStream in) throws IOException {
            List<String> recvContacts;
            synchronized (socketLock) {
                recvContacts = recvUsersNames(in);
            }
            if (!recvContacts.isEmpty()) {
                removeRedundantContacts(recvContacts);
                addNewContacts(recvContacts);
            } else {
                Platform.runLater(() -> contacts.get().clear());
            }
        }

        private void addNewContacts(List<String> recvContacts) {
            for (String s :
                    recvContacts) {
                boolean contain = false;
                for (Contact c :
                        contacts.get()) {
                    if (s.equals(c.getName())) {
                        contain = true;
                        break;
                    }
                }
                if (!contain) {
                    System.out.println("Added: " + s);
                    Platform.runLater(() -> contacts.get().add(new Contact(s)));
                }
            }
        }

        private void removeRedundantContacts(List<String> recvContacts) {
            recvContacts.sort(String::compareTo);
            //remove contacts which aren't in received contacts
            for (Contact c :
                    contacts.get()) {
                boolean rm = true;
                for (String s :
                        recvContacts) {
                    int cmp = c.getName().compareTo(s);
                    if (cmp == 0) {
                        rm = false;
                        break;
                    } else if (cmp < 0)
                        break;
                }
                if (rm) {
                    System.out.println("Deleted: " + c.getName());
                    Platform.runLater(() -> contacts.get().remove(c));
                }
            }
        }

        private boolean authenticate(DataInputStream in, DataOutputStream out) throws IOException, TooLongMessageException {
            synchronized (socketLock) {
                send_authentication_request(out);
                boolean auth = recv_authentication_reply(in);
                recv_authentication_msg(in);
                return auth;
            }
        }

        private void send_authentication_request(DataOutputStream out) throws IOException, TooLongMessageException {
            out.writeByte(SERVER_AUTH_REQUEST);
            int msg_len = hostPassword.length() + clientName.length() + 2;
            if (msg_len > SERVER_BUFFSIZE)
                throw new TooLongMessageException("Too long message sending authenticating request");
            out.writeInt(msg_len);
            out.write((hostPassword + "\0").getBytes(StandardCharsets.US_ASCII));
            out.write((clientName + "\0").getBytes(StandardCharsets.US_ASCII));
            out.flush();
        }

        private void recv_authentication_msg(DataInputStream in) throws IOException {
            int len = in.readInt();
            System.out.println("Read int: " + Integer.toString(len));
            in.readFully(buf.array(), 0, len);
            String string = new String(buf.array(), 0, len);
            System.out.println(string);
        }

        private boolean recv_authentication_reply(DataInputStream in) throws IOException {
            byte msg_type = in.readByte();
            byte msg_subtype = in.readByte();
            if (msg_type == USER_AUTH) {
                switch (msg_subtype) {
                    case USER_AUTH_SUCCESS:
                        return true;
                    case USER_AUTH_FAILURE:
                        return false;
                    default:
                        throw new WrongMsgTypeException("Wrong message's subtype authenticating");
                }
            } else {
                throw new WrongMsgTypeException("Wrong message's type authenticating");
            }
        }
    }

    private class ContactsRequestService extends ScheduledService<Void> {

        @Override
        protected Task<Void> createTask() {
            return new Task<Void>() {

                @Override
                protected Void call() throws Exception {
                    if (waitingForContacts.compareAndSet(false, true))
                        send_contacts_request(outStream);
                    return null;
                }
            };
        }

        void send_contacts_request(DataOutputStream out) throws IOException {
            out.writeByte(SERVER_CONTACTS_REQUEST);
            out.flush();
        }
    }

    private class WrongMsgTypeException extends RuntimeException {
        public WrongMsgTypeException(String msg) {
            super(msg);
        }
    }

    private class TooLongMessageException extends Exception {
        public TooLongMessageException(String msg) {
            super(msg);
        }
    }

}
