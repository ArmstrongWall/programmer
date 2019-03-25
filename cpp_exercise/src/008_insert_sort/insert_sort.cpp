/**
 * @file   insert_sort.cpp
 * @brief  
 * @author Ziqiang Wang
 * @email  ziqiang.wang@uisee.com
 * @Date   19-3-22
 *----------------------------------------------------------------------------*
 *  Remark         : Description                                              *
 *----------------------------------------------------------------------------*
 *  Change History :                                                          *
 *  <Date>     | <Version> | <Author>       | <Description>                   *
 *----------------------------------------------------------------------------*
 *  19-3-22    | 1.0.0.0   | Ziqiang Wang   | Create file                     *
 *----------------------------------------------------------------------------*
 *                                                                            *
 */

#include <vector>
#include "insert_sort.h"

int insert_sort() {

    std::vector<double> rotate_list = {
            20.43126,            20.4341,            20.43616,            20.4391,            20.44106,
            20.4441,            20.44596,            20.44908,            20.45084,            20.45408,
            20.45574,            20.45908,            20.46064,            20.46408,            20.46554,
            20.46906,            20.47044,            20.47406,            20.47534,            20.47906,
            20.48022,
    };

    double t = 10.46519;
    int    i = 0;

    while(true) {
        if(i >= rotate_list.size()) {
            printf("time cls is %f",rotate_list.back());
            break;
        }
        double t_now  = rotate_list[i];
        double t_next = rotate_list[i+1];
        if(t_now < t) {
            if(t_next > t) {
                double t_front = fabs(t_now - t);
                double t_back  = fabs(t_next - t);
                double t_cls   = t_front > t_back ? rotate_list[i+1] : rotate_list[i];
                printf("time cls is %f",t_cls);
                break;
            } else {
                i++;
            }
        } else if(t_now > t) {
            i--;
            if(i <= 0) {
                printf("time cls is %f",rotate_list.front());
                break;
            }
        } else {
            printf("time cls is %f",rotate_list[i]);
            break;
        }
    }
}
