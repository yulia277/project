package com.test.csq.controller;


import com.baomidou.mybatisplus.core.conditions.query.QueryWrapper;
import com.test.csq.common.Dto.*;
import com.test.csq.common.lang.Result;
import com.test.csq.common.lang.ResultList;
import com.test.csq.pojo.User;
import com.test.csq.service.IUserService;

import com.test.csq.user.Message;
import com.test.csq.utils.TokenUtil;
import com.test.csq.utils.ValidatorUtil;
import org.springframework.beans.factory.annotation.Autowired;
import cn.hutool.crypto.SecureUtil;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.multipart.MultipartFile;

import javax.servlet.ServletRequest;
import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.util.Enumeration;
import java.util.List;

/**
 * <p>
 *  前端控制器
 * </p>
 *
 * @author van
 * @since 2022-01-18
 */
@RestController
public class UserController {
    @Autowired
    IUserService iUserService;

    //登录时点击的乃个获取验证码
    @PostMapping("/loginMessage")
    public Result logonMessage(@Validated @RequestBody PhoneDto phoneDto) {
        String phone= phoneDto.getPhone();
        if(!ValidatorUtil.isMobile(phone)) {
            return Result.res(null,200,"手机号码格式错误");
        }
        if(iUserService.findPeo(phone)==null)
            return Result.res(null,200,"请先注册");
        if(iUserService.IsRepeatSend(phone)) {//如果是同一时间重复登录0
            return Result.res(null,200,"请勿重复发送验证码");
        }
        Message message=new Message();
        //获取到验证码
        String tempMessage=message.message(phone);
        //将电话号码和验证码存到redis中
        iUserService.saveMessageToRedis(phone,tempMessage);
        return Result.res(null,500,tempMessage);
    }

    @PostMapping("/login")
    public Result login(@Validated @RequestBody LoginDto loginDto, HttpServletResponse response) {
        String imei=loginDto.getImei();
        User user=null;
        String token=null;
        if(loginDto.getCode()==0) {//账号密码登录/手机号密码登录
            if(ValidatorUtil.isMobile(loginDto.getUsername())) {
                user=iUserService.getOne(new QueryWrapper<User>().eq("phone",loginDto.getUsername()));
            }
            else {
                user=iUserService.getOne(new QueryWrapper<User>().eq("username",loginDto.getUsername()));
            }

            if(null==user)
                return Result.res(null,200,"该用户不存在");
            token= TokenUtil.tokenTest(user.getUsername(),user.getPassword());
            if(!user.getPassword().equals(SecureUtil.md5(loginDto.getPassword()))) {
                return Result.res(null,200,"密码错误");
            }
        }
        else {//验证码登录
            user=iUserService.getOne(new QueryWrapper<User>().eq("phone",loginDto.getPhone()));
            if(null==user)
                return Result.res(null,200,"该用户不存在");
            token= TokenUtil.tokenTest(user.getUsername(),user.getPassword());
            //从redis中获得该手机号对应的验证码
            if(!loginDto.getMessage().equals(iUserService.getMessageFromRedis(loginDto.getPhone()))) {
                return Result.res(null,200,"验证码错误");
            }
        }



        //将token和phone存在一起
        iUserService.saveTokenToRedis(token,user);


        Cookie cookie=new Cookie("token",token);
        response.addCookie(cookie);
//        String key=user.getPhone();
//        String value=user.toString()+imei;
//        iUserService.saveSHAtoRedis(key,value);
        return  Result.res(token,500,"登录成功");
    }


//    点击获取验证码按钮，传手机号"phone":""
    @PostMapping("/getMessage")
    public Result getMessage(@Validated @RequestBody PhoneDto phoneDto) {
        String phone= phoneDto.getPhone();
        if(!ValidatorUtil.isMobile(phone)) {
            //System.out.println(phone);
            return Result.res(null,200,"手机号码格式错误");
        }

        Message message=new Message();
        String tempMessage=message.message(phone);
        iUserService.saveMessageToRedis(phone,tempMessage);
        return Result.res(null,500,tempMessage);
    }

    //点击注册按钮，传用户名，密码，验证码
    @PostMapping("/register")
    public Result register(@Validated @RequestBody RegistDto registDto) {
        if(iUserService.findPeo(registDto.getPhone())!=null)
            return Result.res(null,200,"同一手机只能注册一个账号");
        //如果用户写的验证码与redis中存的一样
        if(registDto.getUsersMessage().equals(iUserService.getMessageFromRedis(registDto.getPhone()))) {
            //将用户写入到数据库中
            User user=iUserService.getOne(new QueryWrapper<User>().eq("username",registDto.getUsername()));
            if(user!=null)
                return Result.res(null,200,"用户已存在");
            User user1=new User();
            user1.setUsername(registDto.getUsername());
            user1.setPhone(registDto.getPhone());
            user1.setPassword(SecureUtil.md5(registDto.getPassword()));
            iUserService.saveUserToDataBase(user1);
            return Result.res(null,500,"注册成功");
        }
        else {
            return Result.res(null,200,"验证码错误");
        }
    }

    //找回密码
    @PostMapping("/nextStep")
    public Result nextStep(@Validated @RequestBody FindDto findDto) {
        if(findDto.getUsersMessage().equals(iUserService.getMessageFromRedis(findDto.getPhone())))
            return Result.res(null,500,"验证码正确");
        return Result.res(null,200,"验证码错误");
    }
    //找回密码
    @PostMapping("/findPassword")
    public Result findBackPassword(@Validated @RequestBody FindDto findDto) {
        findDto.setPassword(SecureUtil.md5(findDto.getPassword()));
        iUserService.revisePassword(findDto.getPhone(),findDto.getPassword());
        return Result.res(null,500,"密码修改成功");
    }

    //上传头像
    @PostMapping("/modification")
    public Result modification(@Autowired @RequestBody MultipartFile file,ServletRequest request) throws IOException {
        //得到照片的url
        String url=iUserService.uploadPhoto(file);
        HttpServletRequest httpServletRequest = (HttpServletRequest) request;

        String token = httpServletRequest.getHeader("token");
        User user=iUserService.getUserFromRedis(token);
        iUserService.saveHeadsulptureToDataBase(user.getId(),url);
        return Result.res(null,500,"上传成功");
    }

    //保存轨迹
    @PostMapping("/upLoadRoad")
    public Result upLoadRoad(@Autowired @RequestBody RunningRecord runningRecord,ServletRequest request) {
        HttpServletRequest httpServletRequest = (HttpServletRequest) request;
        String token = httpServletRequest.getHeader("token");
        String Username=null;
        if(ValidatorUtil.isMobile(runningRecord.getUsername())) {
            User user=iUserService.getUserFromRedis(token);
            runningRecord.setUsername(user.getUsername());
        }
        iUserService.saveRoad(runningRecord);
        return Result.res(null,500,"保存成功");
    }

    //得到轨迹
    @PostMapping("/getRoad")
    public List<RunningRecord> getRoad(@Autowired ServletRequest request) {
        HttpServletRequest httpServletRequest = (HttpServletRequest) request;
        String token = httpServletRequest.getHeader("token");
        User user=iUserService.getUserFromRedis(token);
        String Username=user.getUsername();
        System.out.println(user.getUsername());
        List<RunningRecord> list=iUserService.getRoad(Username);
        return list;
    }

//判断用户是否存在
    @PostMapping("/judgeUsername")
    public Result judge(@Autowired @RequestBody RegistDto registDto) {
        String name=registDto.getUsername();
        if(iUserService.getOne(new QueryWrapper<User>().eq("username",name))!=null) {
            return Result.res(null,200,"该用户名已存在");
        }
        else
            return Result.res(null,500,"用户名可用");
    }

    //存商品信息
    @PostMapping("/goods")
    public Result goods(@Autowired GoodsDto goodsDto) throws IOException {
        MultipartFile file=goodsDto.getFile();
        String url=iUserService.uploadPhoto(file);
        iUserService.saveGoodsInformation(url,goodsDto.getDiscribe());
        return Result.res(null,500,"保存成功");
    }

//存用户补充信息
    @PostMapping("/userInfo")
    public Result supplement(@Autowired @RequestBody UserInfo userInfo,ServletRequest request) {
        HttpServletRequest httpServletRequest = (HttpServletRequest) request;
        String token = httpServletRequest.getHeader("token");
        User user=iUserService.getUserFromRedis(token);
        int id=user.getId();
        iUserService.saveInfo(userInfo.getSex(),userInfo.getHigh(),userInfo.getWeight(),userInfo.getSignature(),userInfo.getBirthday(),id);
        return Result.res(null,500,"保存成功");
    }

    @PostMapping("/community")
    public Result upLoadCommunity(@Autowired @RequestBody CommunityDto communityDto) {
        if(iUserService.upLoadCommunity(communityDto))
            return Result.res(null,500,"保存成功");
        return Result.res(null,200,"保存失败");
    }
    @PostMapping("/getCommunity")
    public List<CommunityDto> getCommunity() {
        List<CommunityDto> list=iUserService.getCommunity();
        return list;
    }

}