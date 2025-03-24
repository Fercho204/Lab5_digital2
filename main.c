/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint16_t Init = 0; // 0: Carrera no iniciada, 1: Carrera en progreso
uint16_t contador1 = 0;
uint16_t DispCont1 = 0;
uint16_t contador2 = 0;
uint16_t DispCont2 = 0;

// Patrones para el display de 7 segmentos (0-5)
uint8_t display_patterns[6] = {
    0b01000000, // 0
    0b11111001, // 1
    0b10100100, // 2
    0b00110000, // 3
    0b10011001, // 4
    0b10010010  // 5
};

void ActDisp1(void);
void ActDisp2(void);
void DisplayNumber(uint8_t number);
void StartRace(void);
void ResetGame(void);
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();

    /* USER CODE BEGIN 2 */
    // Inicializar el display apagado
    DisplayNumber(0);

    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    while (1)
    {
        // Verificar si se ha presionado el botón de inicio
        if (HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == GPIO_PIN_SET) {
            StartRace();
        }

        // Mostrar el estado de los contadores en los LEDs
        HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, (DispCont1 >> 0) & 1);
        HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, (DispCont1 >> 1) & 1);
        HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, (DispCont1 >> 2) & 1);
        HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, (DispCont1 >> 3) & 1);
        HAL_Delay(200);
        HAL_GPIO_WritePin(LED5_GPIO_Port, LED5_Pin, (DispCont2 >> 0) & 1);
        HAL_GPIO_WritePin(LED6_GPIO_Port, LED6_Pin, (DispCont2 >> 1) & 1);
        HAL_GPIO_WritePin(LED7_GPIO_Port, LED7_Pin, (DispCont2 >> 2) & 1);
        HAL_GPIO_WritePin(LED8_GPIO_Port, LED8_Pin, (DispCont2 >> 3) & 1);
        HAL_Delay(200);
        /* USER CODE END WHILE */

        /* USER CODE BEGIN 3 */
    }
    /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    /** Configure the main internal regulator output voltage
    */
    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

    /** Initializes the RCC Oscillators according to the specified parameters
    * in the RCC_OscInitTypeDef structure.
    */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
    RCC_OscInitStruct.PLL.PLLM = 16;
    RCC_OscInitStruct.PLL.PLLN = 336;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
    RCC_OscInitStruct.PLL.PLLQ = 2;
    RCC_OscInitStruct.PLL.PLLR = 2;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }

    /** Initializes the CPU, AHB and APB buses clocks
    */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                                |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
    {
        Error_Handler();
    }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOH_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOC, PIN_a_Pin|PIN_b_Pin|PIN_c_Pin|PIN_d_Pin
                            |PIN_e_Pin|PIN_f_Pin|PIN_g_Pin, GPIO_PIN_RESET);

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOA, LED1_Pin|LED2_Pin|LED3_Pin|LED4_Pin, GPIO_PIN_RESET);

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOB, LED5_Pin|LED6_Pin|LED7_Pin|LED8_Pin, GPIO_PIN_RESET);

    /*Configure GPIO pin : B1_Pin */
    GPIO_InitStruct.Pin = B1_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLDOWN;  // Configuración con pulldown
    HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

    /*Configure GPIO pins : PIN_a_Pin PIN_b_Pin PIN_c_Pin PIN_d_Pin
                           PIN_e_Pin PIN_f_Pin PIN_g_Pin */
    GPIO_InitStruct.Pin = PIN_a_Pin|PIN_b_Pin|PIN_c_Pin|PIN_d_Pin
                          |PIN_e_Pin|PIN_f_Pin|PIN_g_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    /*Configure GPIO pins : BTN_Pin BTN2_Pin */
    GPIO_InitStruct.Pin = BTN_Pin|BTN2_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
    GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /*Configure GPIO pins : LED1_Pin LED2_Pin LED3_Pin LED4_Pin */
    GPIO_InitStruct.Pin = LED1_Pin|LED2_Pin|LED3_Pin|LED4_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /*Configure GPIO pins : LED5_Pin LED6_Pin LED7_Pin LED8_Pin */
    GPIO_InitStruct.Pin = LED5_Pin|LED6_Pin|LED7_Pin|LED8_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* EXTI interrupt init*/
    HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(EXTI0_IRQn);

    HAL_NVIC_SetPriority(EXTI1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(EXTI1_IRQn);
}

/* USER CODE BEGIN 4 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    if (Init == 1) {  // Solo permitir incrementar contadores si la carrera ha comenzado
        if (GPIO_Pin == BTN_Pin) {
            contador1++;
            if (contador1 > 4) contador1 = 0;
            ActDisp1();
        } else if (GPIO_Pin == BTN2_Pin) {
            contador2++;
            if (contador2 > 4) contador2 = 0;
            ActDisp2();
        }

        // Verificar si algún jugador ha ganado
        if (contador1 == 4) {
            DisplayNumber(1); // Mostrar "1" en el display
            Init = 0; // Deshabilitar los botones
        } else if (contador2 == 4) {
            DisplayNumber(2); // Mostrar "2" en el display
            Init = 0; // Deshabilitar los botones
        }
    }
}

void ActDisp1(void) {
    switch (contador1) {
        case 1:
            DispCont1 = 0x1;
            break;
        case 2:
            DispCont1 = 0x2;
            break;
        case 3:
            DispCont1 = 0x4;
            break;
        case 4:
            DispCont1 = 0xF;
            break;
        default:
            DispCont1 = 0x0;
            break;
    }
}

void ActDisp2(void) {
    switch (contador2) {
        case 1:
            DispCont2 = 0x1;
            break;
        case 2:
            DispCont2 = 0x2;
            break;
        case 3:
            DispCont2 = 0x4;
            break;
        case 4:
            DispCont2 = 0xF;
            break;
        default:
            DispCont2 = 0x0;
            break;
    }
}

void DisplayNumber(uint8_t number) {
    if (number > 5) return; // Solo mostramos números del 0 al 5
    HAL_GPIO_WritePin(GPIOC, PIN_a_Pin, (display_patterns[number] >> 0) & 1);
    HAL_GPIO_WritePin(GPIOC, PIN_b_Pin, (display_patterns[number] >> 1) & 1);
    HAL_GPIO_WritePin(GPIOC, PIN_c_Pin, (display_patterns[number] >> 2) & 1);
    HAL_GPIO_WritePin(GPIOC, PIN_d_Pin, (display_patterns[number] >> 3) & 1);
    HAL_GPIO_WritePin(GPIOC, PIN_e_Pin, (display_patterns[number] >> 4) & 1);
    HAL_GPIO_WritePin(GPIOC, PIN_f_Pin, (display_patterns[number] >> 5) & 1);
    HAL_GPIO_WritePin(GPIOC, PIN_g_Pin, (display_patterns[number] >> 6) & 1);
}

void ResetGame(void) {
    // Reiniciar contadores
    contador1 = 0;
    contador2 = 0;
    DispCont1 = 0;
    DispCont2 = 0;

    // Apagar todos los LEDs del jugador 1
    HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, GPIO_PIN_RESET);

    // Apagar todos los LEDs del jugador 2
    HAL_GPIO_WritePin(LED5_GPIO_Port, LED5_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED6_GPIO_Port, LED6_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED7_GPIO_Port, LED7_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED8_GPIO_Port, LED8_Pin, GPIO_PIN_RESET);

    // Mostrar "0" en el display
    DisplayNumber(0);
}

void StartRace(void) {

    // Reiniciar el juego antes de comenzar la carrera
    ResetGame();

    // Iniciar el conteo regresivo
    for (int i = 5; i >= 0; i--) {
        DisplayNumber(i);
        HAL_Delay(1000); // Espera 1 segundo entre cada número
    }

    // Habilitar los botones de los jugadores
    Init = 1;
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
    __disable_irq();
    while (1)
    {
    }
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
    /* USER CODE BEGIN 6 */
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
