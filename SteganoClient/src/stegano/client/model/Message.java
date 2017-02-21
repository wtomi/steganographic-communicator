package stegano.client.model;

import javafx.beans.property.SimpleStringProperty;
import javafx.beans.property.StringProperty;

/**
 * Created by tommy on 19.02.2017.
 */
public class Message {

    public enum Author{
        ME,
        NOT_ME
    }

    private StringProperty message;
    private Author author;

    public Message(String msgText, Author author) {
        message = new SimpleStringProperty((msgText));
        this.author = author;
    }

    public String getMessage() {
       return message.get();
    }

    public void setMessage(String msgText) {
        message.set(msgText);
    }

    public StringProperty getMessageProperty() {
        return message;
    }

    public Author getAuthor() {
        return author;
    }

    public void setAuthor(Author author) {
        this.author = author;
    }

}
