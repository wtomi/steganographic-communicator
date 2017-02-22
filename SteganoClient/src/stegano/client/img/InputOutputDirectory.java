package stegano.client.img;

import javafx.stage.DirectoryChooser;
import stegano.client.MainApp;

import java.io.File;

/**
 * Created by tommy on 22.02.2017.
 */
public class InputOutputDirectory {

    private static File inputDir = null;
    private static File outputDir = null;

    public static File chooseInputDirecotry() {
        DirectoryChooser dirChooser = new DirectoryChooser();
        dirChooser.setTitle("Input Images Directory");
        //File defaultDir = new File("");
        inputDir = dirChooser.showDialog(MainApp.getPrimaryStage());
        return inputDir;
    }

    public static File chooseOutputDirecory() {
        DirectoryChooser dirChooser = new DirectoryChooser();
        dirChooser.setTitle("Output Images Directory");
        //File defaultDir = new File("");
        outputDir = dirChooser.showDialog(MainApp.getPrimaryStage());
        return outputDir;
    }

    public static File getInputDir() {
        return inputDir;
    }

    public static File getOutputDir() {
        return outputDir;
    }

    public static void setInputDir(File inputDir) {
        InputOutputDirectory.inputDir = inputDir;
    }

    public static void setOutputDir(File outputDir) {
        InputOutputDirectory.outputDir = outputDir;
    }
}
