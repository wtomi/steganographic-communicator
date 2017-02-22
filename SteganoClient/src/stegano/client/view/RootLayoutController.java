package stegano.client.view;

import javafx.fxml.FXML;
import javafx.scene.control.Menu;
import javafx.scene.control.MenuBar;
import javafx.scene.control.MenuItem;
import stegano.client.sck.SocketController;


/**
 * Created by tommy on 22.02.2017.
 */
public class RootLayoutController {

    @FXML
    private MenuBar manuBar;
    @FXML
    private Menu menu;
    @FXML
    private MenuItem menuItemDisconnect;

    @FXML
    private void initialize() {
        menuItemDisconnect.setOnAction(event -> {
            SocketController.getInstance().interruptMainLoopThread();
        });
    }


}
