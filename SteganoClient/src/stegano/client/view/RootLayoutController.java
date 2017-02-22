package stegano.client.view;

import javafx.fxml.FXML;
import javafx.scene.control.Menu;
import javafx.scene.control.MenuBar;
import javafx.scene.control.MenuItem;
import stegano.client.img.InputOutputDirectory;
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
    private MenuItem  menuItemInDir;
    @FXML
    private MenuItem menuItemOutDir;

    @FXML
    private void initialize() {
        menuItemDisconnect.setOnAction(event -> SocketController.getInstance().interruptMainLoopThread());
        menuItemInDir.setOnAction(event -> InputOutputDirectory.chooseInputDirecotry());
        menuItemOutDir.setOnAction(event -> InputOutputDirectory.chooseOutputDirecory());
    }


}
