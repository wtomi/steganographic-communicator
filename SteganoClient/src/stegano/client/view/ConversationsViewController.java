package stegano.client.view;

import javafx.collections.MapChangeListener;
import javafx.fxml.FXMLLoader;
import javafx.scene.control.*;
import stegano.client.model.*;
import stegano.client.MainApp;

import javafx.fxml.FXML;

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
                    //System.out.println(userName);
                    addTabToView(userName);
                }
            });
            return cell;
        });

        World.getInstance().getConversations().addListener((MapChangeListener<? super String, ? super Conversation>) change -> {
            String userName = change.getKey();
            addTabToView(userName);
        });
    }

    private void addTabToView(String userName) {
        Tab tab = tabs.get(userName);
        //if tab doesn't exist then create new tab for the chosen user
        if (tab == null) {
            tab = createNewTab(userName);
            tabs.put(userName, tab);
        }
        //if tab is not currently in the tabPane then add it
        if (!tabPane.getTabs().contains(tab)) {
            tabPane.getTabs().add(tab);
        }
        //select tab
        tabPane.getSelectionModel().select(tab);
    }

    private Tab createNewTab(String userName) {
        Tab tab = null;
        try {
            FXMLLoader loader = new FXMLLoader();
            loader.setLocation(MainApp.class.getResource("view/ConversationTabView.fxml"));
            tab = (Tab) loader.load();
            ConversationTabViewController controller = loader.getController();
            controller.setUserName(userName);
            tab.setText(userName);

        } catch (IOException e) {
            e.printStackTrace();
        }
        return tab;
    }
}
