package stegano.client.view;

import javafx.scene.control.TableColumn;
import stegano.client.model.*;
import stegano.client.MainApp;

import javafx.fxml.FXML;
import javafx.scene.control.TableView;

/**
 * Created by tommy on 27.01.2017.
 */
public class ConversationsViewController {

    @FXML
    private TableView<Contact> contactTable;
    @FXML
    private TableColumn<Contact, String> nameColumn;

    //Reference to the mani application
    private MainApp mainApp;

    public ConversationsViewController() {

    }

    /**
     * Initializes the controller class. This method is automatically called
     * after the fxml file has been loaded.
     */
    @FXML
    private void initialize()
    {
        nameColumn.setCellValueFactory(cellData -> cellData.getValue().getNameProperty());
    }

    /**
     * Is called by the main application to give a reference back to itself.
     *
     * @param mainApp
     */
    public void setMainApp(MainApp mainApp) {
        this.mainApp = mainApp;

        // Add observable list data to the table
        contactTable.setItems(mainApp.getContacts());
    }
}
