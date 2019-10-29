//
//  main.cpp
//  krypton
//
//  Created by Jack Zou on 2018/3/5.
//  Copyright © 2018年 jack.zou. All rights reserved.
//

#include <gtest/gtest.h>
#include "test_quantity.h"
#include "ratio_static_check.h"
#include "system_static_check.h"
#include "sequence_static_check.h"
#include "quantity_static_check.h"


int main(int argc, char* argv[]) {
    
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
