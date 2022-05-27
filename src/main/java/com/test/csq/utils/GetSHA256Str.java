package com.test.csq.utils;


import org.apache.commons.codec.binary.Hex;

import java.io.UnsupportedEncodingException;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class GetSHA256Str {
    public static String getSHA256Digest(String str) {
        MessageDigest messageDigest;
        String encdeStr="";
        try {
            messageDigest=MessageDigest.getInstance("SHA_256");
            byte[] hash=messageDigest.digest(str.getBytes("UTF-8"));
            encdeStr= Hex.encodeHexString(hash);
        } catch (NoSuchAlgorithmException e) {
            e.printStackTrace();
        } catch (UnsupportedEncodingException e) {
            e.printStackTrace();
        }

        return encdeStr;
    }

}
