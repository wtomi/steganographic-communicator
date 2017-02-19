package stegano.client.view;

import javafx.fxml.FXMLLoader;
import javafx.scene.control.*;
import stegano.client.model.*;
import stegano.client.MainApp;

import javafx.fxml.FXML;

import java.io.IOException;

/**
 * Created by tommy on 27.01.2017.
 */
public class ConversationsViewController {

    @FXML
    private TableView<Contact> contactTable;
    @FXML
    private TableColumn<Contact, String> nameColumn;
    @FXML
    private TabPane tabPane;

    public ConversationsViewController() {

    }

    /**
     * Initializes the controller class. This method is automatically called
     * after the fxml file has been loaded.
     */
    @FXML
    private void initialize() {
        contactTable.setItems(World.getInstance().getContacts());
        nameColumn.setCellValueFactory(cellData -> cellData.getValue().getNameProperty());
        nameColumn.setCellFactory((TableColumn<Contact, String> tableColumn) -> {
            TableCell<Contact, String> cell = new TableCell<Contact, String>() {
                @Override
                protected void updateItem(String item, boolean empty) {
                    super.updateItem(item, empty);
                    setText(empty ? null : item);
                }
            };
            cell.setOnMouseClicked(e -> {
                if (!cell.isEmpty()) {
                    String userId = cell.getItem();
                    System.out.println(userId);
                }
            });
            return cell;
        });
    }

    private void addNewTab(Contact contact) {
        try {
            FXMLLoader loader = new FXMLLoader();
            loader.setLocation(MainApp.class.getResource("view/ConversationTabView.fxml"));
            Tab tab = (Tab) loader.load();
            tab.setText(contact.getName());
            tabPane.getTabs().add(tab);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
