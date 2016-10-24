//
//  ALBBQuPaiService.h
//  ALBBQuPai
//
//  Created by zhoulai on 15/10/19.
//  Copyright © 2015年 Alibaba. All rights reserved.
//

#import <Foundation/Foundation.h>
#import<UIKit/UIKit.h>

typedef NS_ENUM(NSInteger,QupaiSDKWatermarkPosition){
    QupaiSDKWatermarkPositionTopRight,
    QupaiSDKWatermarkPositionBottomRight,
};

typedef NS_ENUM(NSInteger,QupaiSDKCameraPosition){
    QupaiSDKCameraPositionBack,
    QupaiSDKCameraPositionFront,
};

@protocol QupaiSDKDelegate;

@interface QupaiSDK : NSObject

+ (instancetype)shared;

@property (nonatomic, weak) id<QupaiSDKDelegate> delegte;

@property (nonatomic, assign) BOOL      enableBeauty;                       /* 是否开启美颜切换 */
@property (nonatomic, assign) BOOL      enableImport;                       /* 是否开启导入 */
@property (nonatomic, assign) BOOL      enableMoreMusic;                    /* 是否添加更多音乐按钮 */
@property (nonatomic, assign) BOOL      enableVideoEffect;                  /* 是否开启视频编辑页面 */
@property (nonatomic, assign) BOOL      enableWatermark;                    /* 是否开启水印图片 */
@property (nonatomic, assign) BOOL      enableGuide;                        /* 是否开启引导 */
@property (nonatomic, assign) CGFloat   thumbnailCompressionQuality;        /* 首帧图图片质量:压缩质量 0-1 */
@property (nonatomic, strong) UIColor   *tintColor;                         /* 颜色 */
@property (nonatomic, strong) UIImage   *watermarkImage;                    /* 水印图片 */
@property (nonatomic, assign) QupaiSDKWatermarkPosition watermarkPosition;  /* 水印图片位置 */
@property (nonatomic, assign) QupaiSDKCameraPosition   cameraPosition;     /* 默认摄像头位置，only Back or Front */


/**
 *创建录制页面，需要以 UINavigationController 为父容器
 * @param minDuration 允许拍摄的最小时长
 * @param maxDuration 允许拍摄的最大时长
 * @param bitRate 视频码率，建议800*1000-5000*1000,码率越大，视频越清析，视频文件也会越大。参考：8秒的视频以2000*1000的码率压缩，文件大小1.5M-2M。请开发者根据自己的业务场景设置时长和码率
 */
- (UIViewController *)createRecordViewControllerWithMinDuration:(CGFloat)minDuration
                                                    maxDuration:(CGFloat)maxDuration
                                                        bitRate:(CGFloat)bitRate;

//创建录制页面，需要以 UINavigationController 为父容器
//参数使用默认值
- (UIViewController *)createRecordViewController;

/**
 * 更多音乐有了更新,比如新下载了音乐
 */
- (void)updateMoreMusic;

@end

@protocol QupaiSDKDelegate <NSObject>

/**
 * @param videoPath      保存拍摄好视频的存储路径
 * @param thumbnailPath  保存拍摄好视频首侦图的存储路径
 */
- (void)qupaiSDK:(id<QupaiSDKDelegate>)sdk compeleteVideoPath:(NSString *)videoPath thumbnailPath:(NSString *)thumbnailPath;

@optional
- (NSArray *)qupaiSDKMusics:(id<QupaiSDKDelegate>)sdk;
- (void)qupaiSDKShowMoreMusicView:(id<QupaiSDKDelegate>)sdk viewController:(UIViewController *)viewController;

@end

