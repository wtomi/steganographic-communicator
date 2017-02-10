package stegano.client.model;

import javafx.beans.property.SimpleStringProperty;
import javafx.beans.property.StringProperty;

/**
 * Created by tommy on 27.01.2017.
 */
public class Contact {

    private StringProperty name;

    public Contact(String name)
    {
        this.name = new SimpleStringProperty(name);
    }

    public StringProperty getNameProperty() {
        return name;
    }
}
