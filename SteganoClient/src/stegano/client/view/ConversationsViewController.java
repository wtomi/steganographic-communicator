package stegano.client.view;

import javafx.fxml.FXMLLoader;
import javafx.scene.control.*;
import javafx.scene.paint.*;
import javafx.scene.paint.Color;
import javafx.scene.shape.Rectangle;
import stegano.client.model.*;
import stegano.client.MainApp;

import javafx.fxml.FXML;

import java.awt.*;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

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

    private Map<String, Tab> tabs = new HashMap<>();

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
                    String userName = cell.getItem();
                    System.out.println(userName);

                    Tab tab = tabs.get(userName);
                    if(tab == null) {
                        tab = addNewTab(userName);
                    }
                    tabPane.getSelectionModel().select(tab);
                }
            });
            return cell;
        });
    }


    private Tab addNewTab(String userName) {
        Tab tab = null;
        try {
            FXMLLoader loader = new FXMLLoader();
            loader.setLocation(MainApp.class.getResource("view/ConversationTabView.fxml"));
            tab = (Tab) loader.load();
            tab.setText(userName);
            tabPane.getTabs().add(tab);
            tabs.put(userName, tab);
        } catch (IOException e) {
            e.printStackTrace();
        }
        return tab;
    }
}
