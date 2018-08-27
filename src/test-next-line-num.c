// gnu coreutils/src/cat.c next_line_num
// http://d.hatena.ne.jp/tanakaBox/20070807/1186453144

#include <stdio.h>
#include <stdlib.h>

// 頭悪すぎコメント。
/* Buffer for line numbers.
   An 11 digit counter may overflow within an hour on a P2/466,
   an 18 digit counter needs about 1000y */
#define LINE_COUNTER_BUF_LEN 20
static char line_buf[LINE_COUNTER_BUF_LEN] =
  {
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '0',
    '\t', '\0'
  };

/* Position in `line_buf' where printing starts.  This will not change
   unless the number of lines is larger than 999999.  */
static char *line_num_print = line_buf + LINE_COUNTER_BUF_LEN - 8;

/* Position of the first digit in `line_buf'.  */
static char *line_num_start = line_buf + LINE_COUNTER_BUF_LEN - 3;

/* Position of the last digit in `line_buf'.  */
static char *line_num_end = line_buf + LINE_COUNTER_BUF_LEN - 3;

static void
next_line_num (void)
{
  char *endp = line_num_end; // 最後の数字ポインタ 999
                             //                     ^
  do
    {
      if ((*endp)++ < '9') // 数字をインクリメント桁が増えなければループ終了。
	return;
      *endp-- = '0';       // 990 900 000
    }
  while (endp >= line_num_start); // 新桁がなければここまで(めっさはえぇ)
  
  if (line_num_start > line_buf)
      *--line_num_start = '1'; // 1000 & startを一個増やす
  else
      *line_buf = '>';         // 桁が溢れたら>0000

  if (line_num_start < line_num_print)
    line_num_print--;          // 表示用桁を増やす(初期は6桁)
}

int main(void)
{
    int i;
    for(i = 1; i <= 100000000; i++)
        next_line_num();
    printf("%s\n", line_buf);

    exit(EXIT_SUCCESS);
}
