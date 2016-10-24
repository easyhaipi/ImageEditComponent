//
//  QPLConfiguration.h
//  QPLive
//
//  Created by LYZ on 16/7/23.
//  Copyright © 2016年 lyle. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <CoreGraphics/CoreGraphics.h>
#import <AVFoundation/AVFoundation.h>

typedef NS_ENUM(NSInteger, QP_LCONNECT_STATUS) {
    QPLConnectStatusNone,
    QPLConnectStatusStart,
    QPLConnectStatusSuccess,
    QPLConnectStatusFailed,
    QPLConnectStatusBreak,
};

@interface QPLDebugInfo : NSObject

/*!
 *  摄像头方向
 */
@property (nonatomic, strong) NSString* cameraPresent;

/*!
 *  视频大小
 */
@property (nonatomic, assign) CGSize videoSize;

/*!
 *  连接状态
 */
@property (nonatomic, assign) QP_LCONNECT_STATUS connectStatus;

/*!
 *  时间戳 timeIntervalSince1970
 */
@property (nonatomic, assign) double connectStatusChangeTime;


/*!
 *  当前编码帧数
 */
@property (nonatomic, assign) CGFloat fps;

/*!
 *  编码速度
 */
@property (nonatomic, assign) CGFloat encodeSpeed;

/*!
 *  当前上传速度 单位byte
 */
@property (nonatomic, assign) CGFloat speed;

/*!
 *  本地buffer大小
 */
@property (nonatomic, assign) UInt64 localBufferSize;

/*!
 *  本地buffer音频帧数
 */
@property (nonatomic, assign) UInt64 localBufferAudioCount;


/*!
 *  当前buffer视频帧数
 */
@property (nonatomic, assign) UInt64 localBufferVideoCount;

/*!
 *  编码耗时 单位ms
 */
@property (nonatomic, assign) CGFloat localDelay;


/*!
 *  当前上传数据大小 单位 byte
 */
@property (nonatomic, assign) UInt64 pushSize;


/*!
 *  上一个关键帧dts
 */
@property (nonatomic, assign) CGFloat keyFrameDTS;

/*!
 *  当前输出流video pts
 */
@property (nonatomic, assign) CGFloat currentVideoPTS;

/*!
 *  当前输出流audio pts
 */
@property (nonatomic, assign) CGFloat currentAudioPTS;


/*!
 *  所有编码帧数
 */
@property (nonatomic, assign) NSUInteger encodeFrameCount;

/*!
 *  所有发送帧数
 */
@property (nonatomic, assign) NSUInteger pushFrameCount;

/*!
 *  视频丢帧数
 */
@property (nonatomic, assign) NSInteger videoDiscardFrameCount;

/*!
 *  音频丢帧数
 */
@property (nonatomic, assign) NSInteger audioDiscardFrameCount;

/*!
 *  周期性延迟 单位 ms
 */
@property (nonatomic, assign) double cycleDelay;

/*!
 *  事件信息数组，内部数据结构为打点事件的字典
 */
@property (nonatomic, strong) NSMutableArray *eventArray;

@end


typedef NS_ENUM(NSInteger, QP_LIVE_SCREEN_ORIENTATION) {
    QPLiveScreenVertical = 0,
    QPLiveScreenHorizontal = 1,
};

typedef NS_ENUM(NSInteger, QP_LIVE_WATERMASK_LOCATION) {
    QPLiveWaterMaskLocationRightTop,
    QPLiveWaterMaskLocationLeftTop,
    QPLiveWaterMaskLocationLeftBottom,
    QPLiveWaterMaskLocationRightBottom,
};

@interface QPLConfiguration : NSObject

@property (nonatomic, strong) NSString* preset;
@property (nonatomic, assign) AVCaptureDevicePosition position;
@property (nonatomic, assign) CGSize videoSize;
@property (nonatomic, strong) NSString* url;

/*!
 * 两个取景直接不要黑屏，需要共享previewview
 */
@property (nonatomic, strong) UIView* previewView;

/*!
 * 默认 kVTProfileLevel_H264_High_AutoLevel,
 * 要兼容性好，推荐 kVTProfileLevel_H264_Baseline_AutoLevel
 */
@property (nonatomic, assign) NSString * profileLevel;

/*！
 *  水印位置
 *  默认右上角 可选择左上角，左下角，右上角，右下角
 */
@property (nonatomic, assign) QP_LIVE_WATERMASK_LOCATION waterMaskLocation;


/*!
 *  水印图片
 *  默认无水印
 */
@property (nonatomic, strong) UIImage *waterMaskImage;

/*！
 *  水印图片左上角顶点的x坐标
 *  默认20
 */
@property (nonatomic, assign) CGFloat waterMaskMarginX;

/*！
 *  水印图片左上角顶点的y坐标
 *  默认20
 */
@property (nonatomic, assign) CGFloat waterMaskMarginY;

/**
 *最大码率，网速变化的时候会根据这个值来提供建议码率
 *默认 1500 * 1000
 */
@property (nonatomic, assign) NSInteger videoMaxBitRate;
/*!
 *  最小码率，网速变化的时候会根据这个值来提供建议码率
 *  默认 400 * 1000
 */
@property (nonatomic, assign) NSInteger videoMinBitRate;
/*!
 *  默认码率，在最大码率和最小码率之间
 *  默认 600 * 1000
 */
@property (nonatomic, assign) NSInteger videoBitRate;

/*!
 *  音频码率
 *  默认 64 * 1000
 */
@property (nonatomic, assign) NSInteger audioBitRate;//default 64 * 1000

/*!
 *  帧率
 *  默认 30
 */
@property (nonatomic, assign) NSInteger fps;//default 30

/*!
 *  手机方向 横屏or竖屏
 *  默认 QPLiveScreenVertical 竖屏
 */
@property (nonatomic, assign) QP_LIVE_SCREEN_ORIENTATION screenOrientation;

/*!
 *  调试信息
 */
@property (nonatomic, strong) QPLDebugInfo* debugInfo;

@end
