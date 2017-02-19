package stegano.client.model;

/**
 * Created by tommy on 19.02.2017.
 */
public class Message {
    private String msgText;

    public Message(String msgText) {
        this.msgText = msgText;
    }

    public String getMsgText() {
        return msgText;
    }

    public void setMsgText(String msgText) {
        this.msgText = msgText;
    }
}
