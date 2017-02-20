#include <stdio.h>
#include <stdlib.h>

struct _pid{
  float SetSpeed; //定义设定值
  float ActualSpeed;
  float err;
  float err_last;
  float err_next;
  float Kp,Ki,Kd;
  float umax,umin;
}pid;

void PID_init() {
  printf("PID_init begin \n");
  pid.SetSpeed=0.0;
  pid.ActualSpeed=0.0;
  pid.err=0.0;
  pid.err_last=0.0;
  pid.err_next=0.0;
  pid.Kp=0.4;
  pid.Ki=0.2;
  pid.Kd=0.2;
  pid.umax=400;
  pid.umin=-200;
  printf("PID_init end \n");
}

float PID_realize(float speed){
  pid.SetSpeed=speed;
  pid.err=pid.SetSpeed-pid.ActualSpeed;
  float index;
  if (abs(pid.err)>200) {
    index=0;
  }
  else if (abs(pid.err)<180){
    index=1;
  }
  else {
    index=(200-abs(pid.err))/20;
  }

  float incrementSpeed=pid.Kp*(pid.err-pid.err_next)+index*pid.Ki*pid.err+pid.Kd*(pid.err-2*pid.err_next+pid.err_last);


  pid.ActualSpeed+=incrementSpeed;
  pid.err_last=pid.err_next;
  pid.err_next=pid.err;
  return pid.ActualSpeed;
}

int main() {
  printf("System begin \n");
  PID_init();
  int count=0;
  while (count<100) {
    float speed=PID_realize(200.0);
    printf("%f\n",speed);
    count++;
  }
  return 0;
}
