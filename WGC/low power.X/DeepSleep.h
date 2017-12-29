/* 
 * File:   DeepSleep.h
 * Author: TURONG62
 *
 * Created on 2016年9月21日, 下午4:18
 */

#ifndef DEEPSLEEP_H
#define	DEEPSLEEP_H

#ifdef	__cplusplus
extern "C" {
#endif

    void Start_nod(void); //进入打盹模式
    void Start_Sleep(void);
    void Start_idle(void);
    void OSCChange(u8 NOSCH);
//    u8 GetNowOSC(void);


#ifdef	__cplusplus
}
#endif

#endif	/* DEEPSLEEP_H */

