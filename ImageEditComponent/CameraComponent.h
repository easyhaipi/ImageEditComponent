//
//  CameraComponent.h
//  ImageEditComponent
//
//  Created by taobaichi on 16/10/24.
//  Copyright © 2016年 taobaichi. All rights reserved.
//

#import "SampleBase.h"

@interface CameraComponent : SampleBase
@property(nonatomic,copy)void(^imageBlock)(UIImage *image);//图片处理完成的结果
@end
