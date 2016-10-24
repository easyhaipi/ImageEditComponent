//
//  QPLiveSession.h
//  QPLive
//
//  Created by LYZ on 16/7/23.
//  Copyright © 2016年 lyle. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "QPLConfiguration.h"

typedef NS_ENUM(NSInteger, QP_LIVE_BITRATE_STATUS) {
    QPLiveBitrateRaise,
    QPLiveBitrateDown,
    QPLiveDataDiscard,
};

@protocol QPLiveSessionDelegate;

@interface QPLiveSession : NSObject

/*!
 *  是否开启美颜
 */
@property (nonatomic, assign) BOOL enableSkin;

/*!
 *  闪光灯
 */
@property (nonatomic, assign) AVCaptureTorchMode torchMode;

/*!
 *  摄像头方向
 */
@property (nonatomic, assign) AVCaptureDevicePosition devicePosition;

/*!
 *  QPLiveSessionDelegate
 */
@property (nonatomic, weak) id<QPLiveSessionDelegate> delegate;

@property (nonatomic, assign) QP_LIVE_BITRATE_STATUS bitrateStatus;


/*!
 *  当前版本号
 *
 *  @return 版本号
 */
+ (NSString *)liveVideoVersion;

/*!
 *  init
 *
 *  @param configuration 配置
 *
 *  @return QPLiveSession
 */
- (instancetype)initWithConfiguration:(QPLConfiguration *)configuration;

/*!
 *  预览View
 *
 *  @return 预览View
 */
- (UIView *)previewView;

/*!
 *  开始
 */
- (void)startPreview;

/*!
 *  停止
 */
- (void)stopPreview;

/*!
 *  转换摄像头
 */
- (void)rotateCamera;

/*!
 *  对焦
 *
 *  @param point     位置
 *  @param autoFocus 是否自动对焦
 */
- (void)focusAtAdjustedPoint:(CGPoint)point autoFocus:(BOOL)autoFocus;

/*!
 *  缩放
 *
 *  @param zoom 缩放倍数
 */
- (void)zoomCamera:(CGFloat)zoom;

/**
 *  更改美颜程度
 *
 *  @param value 美颜值
 */
- (void)changeSkinFilterValue:(CGFloat)value;

/*!
 * 更新live配置，可以更新码率和帧率，但是只能在connectServer之前调用
 */
- (void)updateConfiguration:(void(^)(QPLConfiguration *configuration))block;

/*!
 *  推流连接
 */
- (void)connectServer;

/*!
 *  推流连接
 *
 *  @param url 推流URL
 */
- (void)connectServerWithURL:(NSString *)url;

/*!
 *  推流断开连接
 */
- (void)disconnectServer;

/*!
 *  调试信息
 *
 *  @return 调试信息
 */
- (QPLDebugInfo *)dumpDebugInfo;

/*!
 *  当前码率
 *
 *  @return 码率
 */
- (NSInteger)videoBitRate;

@end


@protocol QPLiveSessionDelegate <NSObject>

@required
/*!
 * 推流错误
 */
- (void)liveSession:(QPLiveSession *)session error:(NSError *)error;

/*!
 * 网络很慢，已经不建议直播
 */
- (void)liveSessionNetworkSlow:(QPLiveSession *)session;


@optional
/*!
 * 推流连接成功
 */
- (void)liveSessionConnectSuccess:(QPLiveSession *)session;

/*!
 * 摄像头获取成功
 */
- (void)openVideoSuccess:(QPLiveSession *)session;

/*!
 * 麦克风获取成功
 */
- (void)openAudioSuccess:(QPLiveSession *)session;

/*!
 * 音频设备打开失败
 */
- (void)liveSession:(QPLiveSession *)session openAudioError:(NSError *)error;

/*!
 * 视频设备打开失败
 */
- (void)liveSession:(QPLiveSession *)session openVideoError:(NSError *)error;

/*!
 * 音频编码失败
 */
- (void)liveSession:(QPLiveSession *)session encodeAudioError:(NSError *)error;

/*!
 * 视频编码失败
 */
- (void)liveSession:(QPLiveSession *)session encodeVideoError:(NSError *)error;

/*!
 * 码率变化
 */
- (void)liveSession:(QPLiveSession *)session bitrateStatusChange:(QP_LIVE_BITRATE_STATUS)bitrateStatus;

/*
 *收集日志信息
 */
- (void)liveSession:(QPLiveSession *)session logInfo:(NSDictionary *)info;
@end
