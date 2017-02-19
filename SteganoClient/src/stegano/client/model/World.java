package stegano.client.model;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;

import java.util.HashMap;
import java.util.Map;

/**
 * Created by tommy on 19.02.2017.
 */
public class World {
    private static World ourInstance = new World();

    private ObservableList<Contact> contacts = FXCollections.observableArrayList();
    private Map<String, Conversation> conversations = new HashMap<>();

    public static World getInstance() {
        return ourInstance;
    }

    private World() {
    }

    public ObservableList<Contact> getContacts() {
        return contacts;
    }

    public Map<String, Conversation> getConversations() {
        return conversations;
    }
}
