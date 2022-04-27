//
//  OcrSDKConfig.h
//  OcrSDKKit
//
//  Created by v_clvchen on 2020/7/17.
//  Copyright © 2020 tencent. All rights reserved.
//

#import "OcrSDKConfig.h"
#import "OcrCommDef.h"

NS_ASSUME_NONNULL_BEGIN
//OcrSDKConfig @interface
@interface OcrSDKConfig : NSObject
/// 识别模式
@property (nonatomic, assign) OcrModeType ocrModeType;
/// 自动模式超时时间
@property (nonatomic, assign) long auto_timeout_ms;
// TODU IDCard
/// 身份证照片裁剪（去掉证件外多余的边缘、自动矫正拍摄角度）
@property (nonatomic, assign) BOOL cropIdCard;
///人像照片裁剪（自动抠取身份证头像区域）
@property (nonatomic, assign) BOOL cropPortrait;
///复印件告警
@property (nonatomic, assign) BOOL copyWarn;
///边框和框内遮挡告警
@property (nonatomic, assign) BOOL borderCheckWarn;
/// 翻拍告警
@property (nonatomic, assign) BOOL reshootWarn;
/// PS检测告警
@property (nonatomic, assign) BOOL detectPsWarn;
/// 临时身份证告警
@property (nonatomic, assign) BOOL tempIdWarn;
/// 身份证有效日期不合法告警
@property (nonatomic, assign) BOOL invalidDateWarn;
/// 图片质量分数（评价图片的模糊程度）
@property (nonatomic, assign) BOOL quality;
/// 是否开启多卡证检测
@property (nonatomic, assign) BOOL multiCardDetect;
/// 是否开启反光告警
@property (nonatomic, assign) BOOL reflectWarn;

// TODU BankCard
/// 是否返回预处理（精确剪裁对齐）后的银行卡图片数据
@property (nonatomic, assign) BOOL retBorderCutImage;
///是否返回卡号的切图图片数据
@property (nonatomic, assign) BOOL retCardNoImage;
///复印件检测开关，如果输入的图片是银行卡复印件图片则返回告警
@property (nonatomic, assign) BOOL enableCopyCheck;
///翻拍检测开关，如果输入的图片是银行卡翻拍图片则返回告警
@property (nonatomic, assign) BOOL enableReshootCheck;
///边框遮挡检测开关，如果输入的图片是银行卡边框被遮挡则返回告警
@property (nonatomic, assign) BOOL enableBorderCheck;

// TODU BusinessCardOCR
///图像预处理功能为，检测图片倾斜的角度，将原本倾斜的图片围绕中心点转正，最终输出一张正的名片抠图。
@property (nonatomic, strong) NSString *retImageType;

// TODU MLIDCardOCR
///马来西亚身份证接口是否返回图片
@property (nonatomic, assign) BOOL retImage;
// api请求参数
@property (nonatomic, strong) NSString *requset_opetion;

- (long) getAutoTimeoutms;

@end

NS_ASSUME_NONNULL_END
