package stegano.client.view;

import javafx.concurrent.Task;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;
import java.nio.charset.StandardCharsets;


/**
 * Created by tommy on 17.02.2017.
 */
public class LoginViewController {

    @FXML
    private TextField serverName;

    @FXML
    private TextField serverPort;

    @FXML
    private TextField serverPassword;

    @FXML
    private TextField userName;

    @FXML
    private Button startButton;

    @FXML
    private void initialize() {

        System.out.println("I'm beging initalized");

        startButton.setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent event) {

                Task task = new Task<Void>(){

                    @Override
                    protected Void call() throws Exception {

                        System.out.println("I'm thread and I'm working");

                        Socket socket;
                        DataOutputStream out;
                        DataInputStream in;
                        try {
                            socket = new Socket(serverName.getText(), Integer.valueOf(serverPort.getText()));
                            out = new DataOutputStream(socket.getOutputStream());
                            in = new DataInputStream(socket.getInputStream());

                            out.writeByte(1);
                            out.writeInt(serverPassword.getText().length() + userName.getText().length() + 2);
                            out.write((serverPassword.getText() + "\0").getBytes(StandardCharsets.US_ASCII));
                            out.write((userName.getText() + "\0").getBytes(StandardCharsets.US_ASCII));
                            out.flush();

                            byte msg_type = in.readByte();
                            byte msg_subtype = in.readByte();
                            int len = in.readInt();
                            System.out.println("Read int: " + Integer.toString(len));
                            byte buf[] = new byte[len];
                            in.readFully(buf);
                            String string = new String(buf);
                            System.out.println(string);


                            if(msg_type == 1) {
                                switch (msg_subtype) {
                                    case 1:
                                        System.out.println("Authentication success");
                                        break;
                                    case 2:
                                        System.out.println("Authentication failure");
                                        break;
                                }
                            }
                            Thread.sleep(10000);
                            socket.close();
                        } catch (IOException e) {
                            e.printStackTrace();
                        }
                        return null;
                    }
                };
                Thread t = new Thread(task);
                t.setDaemon(true);
                t.start();

            }
        });
    }

}
