//
//  ViewController.m
//  ImageEditComponent
//
//  Created by taobaichi on 16/10/24.
//  Copyright © 2016年 taobaichi. All rights reserved.
//

#import "ViewController.h"

#import "CameraComponent.h"
#import "EditMultipleComponent.h"
#import <TuSDKGeeV1/TuSDKGeeV1.h>

#import <QPSDK/QPSDK.h>

#define kQPDomain @"baichiwang.s.qupai.me"
@interface ViewController ()<TuSDKFilterManagerDelegate>
{
    
    CameraComponent*  cameraComponentSample;
    EditMultipleComponent *multipleComponentSample;
   
        BOOL _down;
  
    NSString *lastRemoteId;//播放 视频的远程id
}
@property (weak, nonatomic) IBOutlet UIImageView *resultImage;

- (IBAction)doCamerAction:(UIButton *)sender;

- (IBAction)doPhotoAction:(UIButton *)sender;
- (IBAction)createRecord:(UIButton *)sender;

@property (weak, nonatomic) IBOutlet UIButton *playButton;
- (IBAction)playVideoAction:(UIButton *)sender;
@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
   
    
    // 启动GPS
    [[TuSDKTKLocation shared] requireAuthorWithController:self];
    
    [TuSDK checkManagerWithDelegate:self];
    
    // 用户可以通过打印字段的方式获取到正在使用的 SDK 的版本号
    NSLog(@"版本号 : %@",lsqSDKVersion);
    
}

- (void)onTuSDKFilterManagerInited:(TuSDKFilterManager *)manager;
{
    // 可以将方法去掉，不进行初始化完成的提示
    NSLog(@"初始化组件完成");
}
- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


- (IBAction)doCamerAction:(UIButton *)sender {
    
    //相机组件范例
        if (cameraComponentSample == nil)
        {
            cameraComponentSample = [CameraComponent sample];
        }
        cameraComponentSample.imageBlock = ^(UIImage *image){
            self.resultImage.image = image;
         
        };
        [cameraComponentSample showSampleWithController:self];
    
}

- (IBAction)doPhotoAction:(UIButton *)sender {
    
    //照片美化实例
    
    if (multipleComponentSample == nil)
    {
        multipleComponentSample = [EditMultipleComponent sample];
    }
    multipleComponentSample.imageBlock = ^(UIImage *image){
        self.resultImage.image = image;
    
    };
    [multipleComponentSample showSampleWithController:self];
    
}

- (IBAction)createRecord:(UIButton *)sender {
    
    QupaiSDK *sdk = [QupaiSDK shared];
     [sdk setEnableImport:YES];//导入视频
    sdk.enableBeauty = YES;
    sdk.enableVideoEffect = YES;
    [sdk setDelegte:(id<QupaiSDKDelegate>)self];
    
    
    
    /* 基本设置 */
    UIViewController *recordController = [sdk createRecordViewControllerWithMinDuration:5
                                                                            maxDuration:20
                                                                                bitRate:2000000];
    
    [self.navigationController pushViewController:recordController animated:YES];
    
    
    
}

- (void)qupaiSDK:(id <QupaiSDKDelegate>)sdk compeleteVideoPath:(NSString *)videoPath thumbnailPath:(NSString*)thumbnailPath
{
    NSLog(@"Qupai SDK compelete %@",videoPath);
    [self popToRootViewControllerAnimated:YES];
    //保存到了相册
    if (videoPath) {
        UISaveVideoAtPathToSavedPhotosAlbum(videoPath, nil, nil, nil);
    }
    //封面图
//    if (thumbnailPath) {
//        UIImageWriteToSavedPhotosAlbum([UIImage imageWithContentsOfFile:thumbnailPath], nil, nil, nil);
//    }
    
    
    
    [self uploadVideoWithVideoPath:videoPath thumbnailPath:thumbnailPath];
    
}

- (NSArray *)qupaiSDKMusics:(id<QupaiSDKDelegate>)sdk
{
    NSString *baseDir = [[NSBundle mainBundle] bundlePath];
    NSString *configPath = [[NSBundle mainBundle] pathForResource:_down ? @"music2" : @"music1" ofType:@"json"];
    NSData *configData = [NSData dataWithContentsOfFile:configPath];
    NSDictionary *dic = [NSJSONSerialization JSONObjectWithData:configData options:NSJSONReadingAllowFragments error:nil];
    NSArray *items = dic[@"music"];
    
    NSMutableArray *array = [NSMutableArray array];
    for (NSDictionary *item in items) {
        NSString *path = [baseDir stringByAppendingPathComponent:item[@"resourceUrl"]];
        QPEffectMusic *effect = [[QPEffectMusic alloc] init];
        effect.name = item[@"name"];
        effect.eid = [item[@"id"] intValue];
        effect.musicName = [path stringByAppendingPathComponent:@"audio.mp3"];
        effect.icon = [path stringByAppendingPathComponent:@"icon.png"];
        [array addObject:effect];
    }
    return array;
}

-(void)uploadVideoWithVideoPath:(NSString *)videoPath
                  thumbnailPath:(NSString *)thumbnailPath
{
//    NSString *videoPath = [[NSBundle mainBundle] pathForResource:@"Default" ofType:@"mp4"];
//    NSString *thumbnailPath = [[NSBundle mainBundle] pathForResource:@"Default" ofType:@"jpg"];
    
    // 把视频从临时目录拷贝出来，因为下次录制时会清空临时目录。
    NSString *documentPath = [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) firstObject];
    NSString *testDirPath = [documentPath stringByAppendingPathComponent:@"Test"];
    NSFileManager *fileMgr = [NSFileManager defaultManager];
    if (![fileMgr fileExistsAtPath:testDirPath]) {
        [fileMgr createDirectoryAtPath:testDirPath withIntermediateDirectories:NO attributes:nil error:nil];
    }
    NSString *testVideoPath = [testDirPath stringByAppendingPathComponent:[videoPath lastPathComponent]];
    [[NSFileManager defaultManager] copyItemAtPath:videoPath toPath:testVideoPath error:nil];
    
    NSString *testThumbnailPath = [testDirPath stringByAppendingPathComponent:[thumbnailPath lastPathComponent]];
    [[NSFileManager defaultManager] copyItemAtPath:thumbnailPath toPath:testThumbnailPath error:nil];
    
    //创建上传任务
    QPUploadTask *task = [[QPUploadTaskManager shared] createUploadTaskWithVideoPath:testVideoPath thumbnailPath:testThumbnailPath];
    
   
    
    [[QPUploadTaskManager shared] startUploadTask:task progress:^(CGFloat progress) {
        dispatch_async(dispatch_get_main_queue(), ^{
            self.playButton.hidden = YES;
             NSLog(@"上传进度%f",progress);
        });
    } success:^(QPUploadTask *uploadTask, NSString *remoteId) {
        dispatch_async(dispatch_get_main_queue(), ^{
            self.playButton.hidden = NO;
            NSLog(@"%@",remoteId);
            
            self->lastRemoteId = remoteId;
            NSLog(@"视频上传成功");
          
        });
    } failure:^(NSError *error) {
        dispatch_async(dispatch_get_main_queue(), ^{
             NSLog(@"upload failed");
        });
    }];
}


- (IBAction)playVideoAction:(UIButton *)sender {
    
    NSString *accessToken = [[NSUserDefaults standardUserDefaults] objectForKey:@"accessToken"];
   
    
    
    NSString *videoString = [NSString stringWithFormat:@"http://%@/v/%@.mp4?token=%@", kQPDomain, self->lastRemoteId, accessToken];
    [[UIApplication sharedApplication] openURL:[NSURL URLWithString:videoString]];

}
@end
