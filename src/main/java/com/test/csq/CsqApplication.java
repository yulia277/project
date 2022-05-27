package com.test.csq;


import org.mybatis.spring.annotation.MapperScan;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;


@SpringBootApplication
@MapperScan("com.test.csq.mapper")

public class CsqApplication {

    public static void main(String[] args) {
        SpringApplication.run(CsqApplication.class, args);
    }

}
