package com.test.csq.utils;

import java.util.UUID;

public class UUidUtils {
    public static String uuid() {
        return UUID.randomUUID().toString().replace("-", "");
    }
}
