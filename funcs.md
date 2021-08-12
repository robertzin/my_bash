readline - char *readline (const char *prompt) - The function readline() prints a prompt and then reads and returns a single line of text from the user. If prompt is NULL or the empty string, no prompt is displayed. The line readline returns is allocated with malloc(); the caller should free() the line when it has finished with it.

rl_clear_history - int rl_clear_history() -  очищает историю комнад в промпте

rl_on_new_line - int rl_on_new_line (void) - tell the update functions that we have moved onto a new (empty) line, usually after outputting a newline.

rl_replace_line - void rl_replace_line (const char *text, int clear_undo) - Replace the contents of rl_line_buffer with text. The point and mark are preserved, if possible. If clear_undo is non-zero, the undo list associated with the current line is cleared.

rl_redisplay - void rl_redisplay (void) - change what's displayed on the screen to reflect the current contents of rl_line_buffer.
add_history - int add_history(const char *) - добавляет историю с командной строки в полученный аргумент

-lreadline -L /Users/$USER/.brew/opt/readline/lib -I/Users/$USER/.brew/opt/readline/include

printf
malloc
free

write
open
read
close

fork, wait
waitpid
wait3
wait4

signal
kill
exit

getcwd - char *getcwd(char *buf, size_t size) - Возвращает указатель на buf в случае успеха, NULL — в случае ошибки. 
chdir - int chdir(const char *pathname) - меняет рабочий каталог на  pathname (указатель на строку или фд). Возвращает 0 в случае успеха и -1 при ошибке

stat -	int stat(const char *file_name, struct stat *buf)
	stat возвращает информацию о файле file_name и заполняет буфер buf. lstat идентична stat, но в случае 	символьных сылок она возвращает информацию о самой ссылке, а не о файле, на который она 	указывает. fstat идентична stat, только возвращается информация об открытом файле, на который 	указывает filedes (возвращаемый open(2)), а не о file_name.
lstat -	int lstat(const char *file_name, struct stat *buf)
fstat -	int fstat(int filedes, struct stat *buf)
	Функция stat возвращает структуру с информацией о файле, указанном в аргу- менте pathname. Функция 	fstat возвращает информацию об открытом файле по его дескриптору fd. Функция lstat похожа на 	функцию stat, но когда ей пере- дается имя символической ссылки, она возвращает сведения о самой 	символиче- ской ссылке, а не о файле, на который она ссылается. 


struct stat {
    dev_t         st_dev;      /* устройство */
    ino_t         st_ino;      /* inode */
    mode_t        st_mode;     /* режим доступа */
    nlink_t       st_nlink;    /* количество жестких ссылок */
    uid_t         st_uid;      /* идентификатор пользователя-владельца */
    gid_t         st_gid;      /* идентификатор группы-владельца */
    dev_t         st_rdev;     /* тип устройства */
                               /* (если это устройство) */
    off_t         st_size;     /* общий размер в байтах */
    blksize_t     st_blksize;  /* размер блока ввода-вывода */
                               /* в файловой системе */
    blkcnt_t      st_blocks;   /* количество выделенных блоков */
    time_t        st_atime;    /* время последнего доступа */
    time_t        st_mtime;    /* время последней модификации */
    time_t        st_ctime;    /* время последнего изменения */
};


Все возвращают 0 в случае успеха, –1 — в случае ошибки 
unlink

execve
dup
dup2
pipe

opendir - DIR *opendir(const char *pathname) - Функция opendir() открывает поток каталога, соответствующий каталогу name, и возвращает указатель на этот поток. Поток устанавливается на первой записи в каталоге. Возвращает указатель в случае успеха или NULL — в случае ошибки  
readdir - struct dirent *readdir(DIR *dir) - Функция readdir() возвращает указатель на структуру dirent или NULL в случае ошибки или по достижении последней записи
closedir - int closedir(DIR *dp) - Функция closedir() закрывает поток, связанный с каталогом dir. Описатель потока dir будет недоступен после вызова этой функции. Возвращает 0 в случае успеха или –1 — в случае ошибки. 


strerror
errno

isatty - int isatty(int fd) - возвращает 1, если фд указывает на терминал, и 0, если нет
ttyname - char *ttyname(int fd) - Функция ttyname() возвращает указатель на полное имя устройства терминала, заканчивающееся на NUL, открытого на описателе файла fd, или NULL при ошибках (например, если fd не подключен к терминалу). Возвращаемое значение может указывать на статические данные, которые могут быть перезаписаны следующим вызовом. Возвращает указатель на имя или  NULL.
ttyslot - int ttyslot(void) - функция извлекает номер управляющего терминала текущего процесса из записи файла ttys (5)
ioctl - управление устройством посредством аргумеентов в иокл (открыть сд ром, например), можно отследить размер терминала. В зависимости от этого определяем, когда переходить на следующую строку

unset - удаляем пару переменная=значение из окружения

getenv - char *getenv(const char *name) - чтение окружения (stdlib.h); Функция эта работает очень просто: если в качестве аргумента указано имя существующей переменной окружения, то функция возвращает указатель на строку, содержащую значение этой переменной; если переменная отсутствует, возвращается NULL.

char * getenv (const char * name)
int main (int argc, char ** argv)
{
    char    *env;
    char    *path;

    env = "PATH";
    path = getenv(env);
    printf ("%s=%s\n", env, path);
    return (0);
}

Забираем аттрибуты терминала и меняем их. 
tcsetattr - изменение служебных символов - int tcsetattr(int fd, int opt, const struct termios *termptr); 
tcgetattr - int tcgetattr(int fd, struct termios *termptr);

tgetent - вызываем информацию по терминалу 
tgetflag
tgetnum
tgetstr
tgoto
tputs


Структура программы  
1 - запускаем цикл readline, через который получаем команды со строки
2 - препарсинг. проверяем строку на наличие незакрытых кавычек и \
3 - парсим строку:
	обрабатываем специальные символы: \, ', ", $, >, >>, < (видео с нотион)
	читаем команды и помещаем их в таблицу команд (массив? листы?)
4 - передаем таблицу на исолнение
5 - сигналы? невыход по ctrl+c?
	