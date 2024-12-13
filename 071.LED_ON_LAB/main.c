// 이 부분은 임의로 바꾸지 마시오
#define RCC_APB2ENR   (*(unsigned long*)0x40021018)

// 여기에 사용자 임의의 define을 작성하시오
// 여기에 사용자 임의의 define을 작성하시오
#define GPIOB_CRH   (*(unsigned long*)0x40010C04)
#define GPIOB_ODR   (*(unsigned long*)0x40010C0C)


void Main(void)
{
    // 이 부분은 임의로 바꾸지 마시오
    RCC_APB2ENR |= (1<<3);

    // GPB[9:8]을 출력 모드로 설정하시오
    GPIOB_CRH = ((0x3 << 4) | (0x3 << 0));
    // GPB[9:8]에 LED0은 OFF, LED1은 ON 시키도록 설정하시오

    GPIOB_ODR = 0x00000100;   // LED1 (PB9) ON

}
