//
//  TXYLog.h
//  TXCloudiOSCommon
//
//  Created by v_clvchen on 2020/11/3.
//  Copyright © 2020 tencent. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

#ifdef DEBUG
#define MyCLLogInfo(fmt, ...) NSLog((@"%s [Line %d] " fmt), __PRETTY_FUNCTION__, __LINE__, ##__VA_ARGS__);
#else
#define MyCLLogInfo(...)
#endif


#define TXYLog(frmt,...) [TXYLog logWithLine:__LINE__ method:[NSString stringWithFormat:@"%s", __FUNCTION__] \
time:[NSDate date] \
format:[NSString stringWithFormat:frmt, ## __VA_ARGS__]]


//TXYLog @interface
@interface TXYLog : NSObject


+ (void) setDebugPrintLog:(BOOL)isDebug;

+ (void)logWithLine:(NSUInteger)line
             method:(NSString *)methodName
               time:(NSDate *)timeStr
             format:(NSString *)format;

@end

NS_ASSUME_NONNULL_END
