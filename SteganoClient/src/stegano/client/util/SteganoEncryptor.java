package stegano.client.util;

import com.sun.deploy.util.ArrayUtil;

import javax.rmi.CORBA.Util;
import java.nio.charset.StandardCharsets;
import java.util.LinkedList;
import java.util.List;

/**
 * Created by tommy on 09.02.2017.
 */
public class SteganoEncryptor {

    static public byte[] encryptData(byte[] imageData, String text){

        final int LETTER_LEN_IN_BITS = 8;

        int textLength = text.length();
        int maxTextLength = (imageData.length)/LETTER_LEN_IN_BITS - 1; //-1 because the message ends with NULL byte

        if(textLength > maxTextLength)
            throw new IllegalArgumentException("Text is too long to be encrypted in the image!");

        byte[] textASCII = (text + "\0").getBytes(StandardCharsets.US_ASCII);

        int num_of_bit = 0;
        int letter_idx = 0;
        for(int i = 0; letter_idx < textASCII.length; i++) {
            imageData[i] = (byte) ((imageData[i] & (byte) 0xFE) | ((textASCII[letter_idx] >> num_of_bit) & (byte) 0x01));
            num_of_bit++;
            if (num_of_bit > 7) {
                num_of_bit = 0;
                letter_idx++;
            }
        }

        return imageData;
    }

    static  public String decryptData(byte[] imageData){

        List<Byte> textData = new LinkedList<>();
        int num_of_bit = 0;
        int letter_idx = 0;
        byte letter = 0;
        for(int i = 0; i < imageData.length; i++)
        {
            if(num_of_bit > 7)
            {
                num_of_bit = 0;
                letter_idx++;

                if(letter == 0)
                    break;
                textData.add(new Byte(letter));
                letter = 0;
            }
            letter |= (imageData[i] & 0x01) << num_of_bit;
        }

        byte[] byteTextData = new byte[textData.size()];
        int i = 0;
        for (Byte l: textData) {
            byteTextData[i] = l;
            i++;
        }

        String text = new String(byteTextData, StandardCharsets.US_ASCII);
        return text;
    }
}
