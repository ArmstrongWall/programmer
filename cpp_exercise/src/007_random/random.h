/**
 *
 * @file   random.h
 * @brief  
 * @author Ziqiang Wang
 * @email  ziqiang.wang@uisee.com
 * @Date   19-3-7
 *----------------------------------------------------------------------------*
 *  Remark         : Description                                              *
 *----------------------------------------------------------------------------*
 *  Change History :                                                          *
 *  <Date>     | <Version> | <Author>       | <Description>                   *
 *----------------------------------------------------------------------------*
 *  19-3-7    | 1.0.0.0   | Ziqiang Wang   | Create file                     *
 *----------------------------------------------------------------------------*
 *                                                                            *
 */

#ifndef CPP_EXERCISE_RANDOM_H
#define CPP_EXERCISE_RANDOM_H
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define random(x) (rand()%x)

int r() {
    srand((int)time(0));
    for(int x=0;x<10;x++)
        printf("%d\n",random(100));

}
#endif //CPP_EXERCISE_RANDOM_H
