package stegano.client.view;

import javafx.concurrent.Task;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.input.KeyCode;
import stegano.client.model.Message;
import stegano.client.model.World;
import stegano.client.sck.SocketController;

/**
 * Created by tommy on 19.02.2017.
 */
public class ConversationTabViewController {

    public ConversationTabViewController() {

    }

    @FXML
    private TextArea msgTextArea;
    @FXML
    private ListView<Message> conversationListView;
    @FXML
    private Tab tab;

    private String userName;

    @FXML
    private void initialize() {


        msgTextArea.setOnKeyPressed(event -> {
            if (event.getCode() == KeyCode.ENTER) {
                String msgText = msgTextArea.getText();
                Task sendMsgTask = SocketController.getInstance().getSendMsgTask(userName, msgText);
//                sendMsgTask.setOnSucceeded(event1 -> {
//                    if(sendMsgTask.getValue() == Boolean.TRUE)
//                        World.getInstance().getConversation(userName).addMessage(new Message(msgText, Message.Author.ME));
//                    else {
//                        //TODO sending message failure feedback
//                    }
//                });
                Thread t = new Thread(sendMsgTask);
                t.setDaemon(true);
                t.start();
                msgTextArea.positionCaret(0);
                msgTextArea.clear();
                event.consume();
            }
        });

        conversationListView.setCellFactory(listView -> new ListCell<Message>() {

            @Override
            protected void updateItem(Message item, boolean empty) {
                super.updateItem(item, empty);
                if (empty || item == null) {
                    setGraphic(null);
                    setText(null);
                } else {
                    Label text = new Label();
                    text.setWrapText(true);
                    //text.wrappingWidthProperty().bind(conversationListView.widthProperty().subtract(15));
                    text.textProperty().bind(item.getMessageProperty());
                    setGraphic(text);
                    setPrefWidth(0);
                    //setText(item.getMessage());
                    if (item.getAuthor() == Message.Author.ME) {
                        setStyle("-fx-alignment: CENTER-RIGHT;");
                        text.setStyle("-fx-text-alignment: right;" +
                                "-fx-background-color: lightcyan;");
                    } else {
                        setStyle("-fx-alignment: CENTER-LEFT;");
                        text.setStyle("-fx-text-alignment: left;" +
                                "-fx-background-color: lightgrey");

                    }
                }
            }

        });
    }

    public String getUserName() {
        return userName;
    }

    public void setUserName(String userName) {
        this.userName = userName;
        conversationListView.setItems(World.getInstance().getConversation(userName).getMessages());
    }
}
