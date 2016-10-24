//
//  ViewController.m
//  ImageEditComponent
//
//  Created by taobaichi on 16/10/24.
//  Copyright © 2016年 taobaichi. All rights reserved.
//

#import "ViewController.h"


#import <TuSDKGeeV1/TuSDKGeeV1.h>
@interface ViewController ()<TuSDKFilterManagerDelegate>
@property (weak, nonatomic) IBOutlet UIImageView *resultImage;

- (IBAction)doCamerAction:(UIButton *)sender;

- (IBAction)doPhotoAction:(UIButton *)sender;

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
}

- (IBAction)doPhotoAction:(UIButton *)sender {
}
@end
