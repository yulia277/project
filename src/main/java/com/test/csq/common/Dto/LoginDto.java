package com.test.csq.common.Dto;


import lombok.Data;

@Data
public class LoginDto {
    private int code;//用来表示是账密还是手机验证码登录，0表示账密，1表示手机号码
    private String username;
    private String password;
    private String phone;//手机号码
    private String imei;
    private String message;//如果是手机验证码的话，这个就代表是用户写的哪个message

}
