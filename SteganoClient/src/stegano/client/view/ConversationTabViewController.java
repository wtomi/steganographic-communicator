package stegano.client.view;

import javafx.fxml.FXML;
import javafx.scene.control.ListCell;
import javafx.scene.control.ListView;
import javafx.scene.control.Tab;
import javafx.scene.control.TextArea;
import javafx.scene.input.KeyCode;
import stegano.client.model.Message;

import java.awt.event.KeyEvent;

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

    @FXML
    private void initialize() {

        msgTextArea.setOnKeyPressed(event -> {
            if(event.getCode() == KeyCode.ENTER) {
                String text = msgTextArea.getText();

                msgTextArea.clear();
            }
        });

        conversationListView.setCellFactory(listView -> new ListCell<Message>() {

            @Override
            protected void updateItem(Message item, boolean empty) {
                super.updateItem(item, empty);
                    setText(item.getMessage());
                    if(item.getAuthor() == Message.Author.ME) {
                        setStyle("-fx-alignment: CENTER-RIGHT;" +
                                "-fx-background-color: lightcyan;");
                    }
                    else {
                        setStyle("-fx-alignment: CENTER-LEFT;" +
                                "-fx-background-color: lightgrey");
                    }
            }
        });

        }
}
