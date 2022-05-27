package com.test.csq.utils;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class ValidatorUtil {
    private static final Pattern mobile_pattern=Pattern.compile("^((13[0-9])|(15[^4])|(18[0,2,3,5-9])|(17[0-8])|(147))\\d{8}$");

    public static boolean isMobile(String mobile) {
        if(null==mobile)
            return false;
        Matcher matcher=mobile_pattern.matcher(mobile);
        return matcher.matches();
    }
}
