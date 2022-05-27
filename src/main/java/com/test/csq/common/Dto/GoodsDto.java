package com.test.csq.common.Dto;

import lombok.Data;
import org.springframework.web.multipart.MultipartFile;

@Data
public class GoodsDto {
    MultipartFile file;
    String discribe;
}
