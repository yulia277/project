package com.test.csq.controller;

import com.alibaba.fastjson.JSON;
import com.alibaba.fastjson.JSONObject;
import com.test.csq.common.lang.Result;
import com.test.csq.pojo.User;
import com.test.csq.service.IUserService;
import com.test.csq.utils.BodyReaderHttpServletRequestWrapper;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.redis.core.RedisTemplate;
import org.springframework.data.redis.core.ValueOperations;
import org.springframework.stereotype.Component;
import javax.servlet.*;
import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServletRequest;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Enumeration;
import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.TimeUnit;

//@Component
//public class MyFilter implements Filter {
//    @Autowired
//    private RedisTemplate redisTemplate;
//
//    @Override
//    public void init(FilterConfig filterConfig) throws ServletException {
//
//    }
//
//    @Override
//    public void doFilter(ServletRequest request, ServletResponse response, FilterChain filterChain) throws IOException, ServletException {
//        request.setCharacterEncoding("utf-8");
//        response.setContentType("text/html;charset=utf-8");
//
//        if (request instanceof HttpServletRequest) {
//            HttpServletRequest httpServletRequest = (HttpServletRequest) request;
//            String token = httpServletRequest.getHeader("token");
//            if(redisTemplate.hasKey(token)) {
//                ValueOperations ops=redisTemplate.opsForValue();
//                User user=(User)ops.get(token);
//                ops.set(token,user,30,TimeUnit.DAYS);
//                filterChain.doFilter(request,response);
//            }
//            //能到这里来说明是没有token
//            PrintWriter out=response.getWriter();
//            out.write(JSON.toJSONString(Result.res(null,200,"未登录")));
//
//        }
//    }
//
//    @Override
//    public void destroy() {
//
//    }
//}
