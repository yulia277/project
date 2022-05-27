package com.test.csq.common.Dto;


import lombok.Data;

@Data
public class RegistDto {
    private String username;
    private String password;
    private String phone;
    private String usersMessage;//用户写的短信验证码
}
