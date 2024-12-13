// �� �κ��� ���Ƿ� �ٲ��� ���ÿ�
#define RCC_APB2ENR   (*(unsigned long*)0x40021018)

// ���⿡ ����� ������ define�� �ۼ��Ͻÿ�
// ���⿡ ����� ������ define�� �ۼ��Ͻÿ�
#define GPIOB_CRH   (*(unsigned long*)0x40010C04)
#define GPIOB_ODR   (*(unsigned long*)0x40010C0C)


void Main(void)
{
    // �� �κ��� ���Ƿ� �ٲ��� ���ÿ�
    RCC_APB2ENR |= (1<<3);

    // GPB[9:8]�� ��� ���� �����Ͻÿ�
    GPIOB_CRH = ((0x3 << 4) | (0x3 << 0));
    // GPB[9:8]�� LED0�� OFF, LED1�� ON ��Ű���� �����Ͻÿ�

    GPIOB_ODR = 0x00000100;   // LED1 (PB9) ON

}
