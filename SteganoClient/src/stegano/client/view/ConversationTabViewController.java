package stegano.client.view;

import javafx.fxml.FXML;
import javafx.scene.control.ListView;
import javafx.scene.control.TextArea;

/**
 * Created by tommy on 19.02.2017.
 */
public class ConversationTabViewController {

    public ConversationTabViewController() {

    }

    @FXML
    private TextArea msgTextArea;
    @FXML
    private ListView<String> conversationListView;

    @FXML
    private void initialize() {
    }


}
