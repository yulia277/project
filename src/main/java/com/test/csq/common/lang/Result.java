package com.test.csq.common.lang;

import com.baomidou.mybatisplus.extension.api.R;
import lombok.Data;

@Data
public class Result {
    String data;
    int code;
    String message;

    public static Result res(String data, int code, String message) {
        Result result=new Result();
        result.setData(data);
        result.setCode(code);
        result.setMessage(message);
        return result;
    }
}
