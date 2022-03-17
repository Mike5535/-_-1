#include "input.h"

void set_ptr_null(Product* pp)
{
    pp->name = NULL;
    pp->product_class = NULL;
    pp->number = NULL;
    pp->install_data = NULL;
    pp->update_data = NULL;
}


char* get_string(FILE* ptemp, char end)
{
    char* buffer = NULL;                   //буфер для хранения символов
    unsigned int capacity = 0;              //размер буфера
    unsigned int n = 0;                 //сколько символов в буфере
    int bitofchar = sizeof(char);           //сколько бит в char
    int MAX_LEN = 2048;                 // 1 строка максимум 4 Мб (MAX_LEN*2)
    int c;                              //сюда записываем символы
    // получаем символы со стандартного ввода (клавиатура или файл)
    while ((c = fgetc(ptemp)) != end && c != EOF && c != '\n' && c != ' ')
    {
        // при необходимости увеличиваем размер буфера
        if (n + 1 > capacity)
        {
            if (!capacity)                      //если буфера нет: if (capacity == 0)
                capacity = 32;                  //задаем новый, по умолчанию 32 символа
            else if (capacity <= MAX_LEN)
                capacity *= 2;                  //если размер исчерпан, удваиваем
            else                                    //иначе (угроза переполнения буфера):
            {                                       //освобождаем память и выходим
                free(buffer);
                return NULL;
            }

            // меняем реальный размер буфера в памяти
            char* temp = (char*)realloc(buffer, capacity * bitofchar);
            if (!temp)                          //if (temp == NULL)
            {
                free(buffer);
                return NULL;
            }
            buffer = temp;                      //перезаписываем буфер
        }

        buffer[n++] = c;                        //добавляем текущий символ в буфер
    }

    // если пользователь ввел пустую строку, возвращаем NULL
    if ((n == 0 && c == EOF) || (n == 0 && c == '\n'))
    {
        if (buffer) free(buffer);
        return NULL;
    }

    if (c == ' ')
    {
        char c;
        while ((c = fgetc(ptemp)) != '\n')
            ;
    }
    // минимизируем размер буфера
    char* minimal = (char*)malloc((n + 1) * bitofchar);
    strncpy(minimal, buffer, n);
    free(buffer);

    minimal[n] = '\0';                      //добавляем конец строки

    return minimal;                         //возвращаем получившуюся строку
}




void clean_input_product(FILE* ptemp)
{
    char* c = (char*)malloc(2 * sizeof(char));
    c[0] = fgetc(ptemp);
    c[1] = fgetc(ptemp);
    size_t i = 1;
    while (c[1] != '\n' || c[0] != '\n')
    {
        i == 1 ? i-- : i++;
        c[i] = fgetc(ptemp);
    }
    free(c);
}

bool chek_string(char* temp, bool f)
{
    if (temp == NULL) return false;
    size_t i = 0;
    bool flag = false;
    while (temp[i] != '\0')
    {
        if ((f || temp[i] < 'A' || temp[i] > 'Z') && (f || temp[i] < 'a' || temp[i] > 'z') && (temp[i] - '0' < 0 || temp[i] - '0' > 9))
            flag = true;
        i++;
    }
    return flag;
}

size_t* get_data(FILE* pfile)
{
    size_t* temp = (size_t*)malloc(size * sizeof(size_t));

    char* chek = get_string(pfile, '.');
    if (chek == NULL)
    {
        free(temp);
        return NULL;
    }
    if (chek_string(chek, true) == false)
    {
        int prom = atoi(chek);
        if (prom < 32 && prom > 0)
            temp[0] = prom;
        else
        {
            free(chek);
            free(temp);
            return NULL;
        }
    }
    else
    {
        free(chek);
        free(temp);
        return NULL;
    }
    free(chek);


    chek = get_string(pfile, '.');
    if (chek == NULL)
    {
        free(temp);
        return NULL;
    }
    if (chek_string(chek, true) == false)
    {
        int prom = atoi(chek);
        if (prom < 13 && prom > 0)
            temp[1] = prom;
        else
        {
            free(chek);
            free(temp);
            return NULL;
        }
    }
    else
    {
        free(chek);
        free(temp);
        return NULL;
    }
    free(chek);



    chek = get_string(pfile, ' ');
    if (chek == NULL)
    {
        free(temp);
        return NULL;
    }
    if (chek_string(chek, true) == false)
    {
        int prom = atoi(chek);
        if (prom < 2023 && prom > 0)
            temp[2] = prom;
        else 
        {
            free(chek);
            free(temp);
            return NULL;
        }
    }
    else
    {
        free(chek);
        free(temp);
        return NULL;
    }
    free(chek);

    return temp;
}




bool get_product(Product* temp, FILE* pfile)
{
    set_ptr_null(temp);
    temp->name = get_string(pfile, ' ');
    if (temp->name == NULL)
    {
        return false;
    }
    if (chek_string(temp->name, false))
    {
        free(temp->name);
        temp->name = NULL;
        clean_input_product(pfile); // позволяет игнорировать оставшиеся данные неправильной записи
        return true;

        //все записи обязательны, кроме даты обновления
    }

    
    temp->product_class = get_string(pfile, ' ');
    if (temp->product_class == NULL)
    {
        return true;
        //все записи обязательны, кроме даты обновления
    }
    if (chek_string(temp->product_class, false))
    {
        free(temp->product_class);
        temp->product_class = NULL;
        clean_input_product(pfile); // позволяет игнорировать оставшиеся данные неправильной записи
        return true;
    }
    //flush_input();
    temp->number = get_string(pfile, ' ');
    if (temp->number == NULL)
    {
        return true;
        //все записи обязательны, кроме даты обновления
    }
    if (chek_string(temp->number, false))
    {
        free(temp->number);
        temp->number = NULL;
        clean_input_product(pfile); // позволяет игнорировать оставшиеся данные неправильной записи
        return true;
    }
    //flush_input();
    temp->install_data = get_data(pfile);
    if (temp->install_data == NULL)
    {
        return true;
        //все записи обязательны, кроме даты обновления
    }

    // flush_input();
    temp->update_data = get_data(pfile);
    if (temp->update_data == NULL)
    {
        return true;
    }

    return true;
}

void free_product(Product* f)
{
    free(f->name);
    free(f->product_class);
    free(f->number);
    free(f->update_data);
    free(f->install_data);
}

Product* chek_null(Product* temp)
{
    if (temp->name == NULL || temp->number == NULL || temp->product_class == NULL || temp->install_data == NULL)
    {
        if (temp->name != NULL)
            free_product(temp);
        free(temp);
        temp = NULL;
    }
    return temp;
}

Product** innput(FILE* p_in, size_t* pi)
{
    Product** all = (Product**)malloc(sizeof(Product*));
    bool f1 = false;  // было ли что-то в потоке
    bool f2 = false;
    all[0] = (Product*)malloc(sizeof(Product));


    size_t i = 0;

    if (get_product(all[i], p_in) == 1)
        f1 = true; // чет
    all[i] = chek_null(all[i]);

    size_t count = 0;

    if (f1 == true)
    {
        do
        {
            if (all[i] != NULL)
            {
                if (all[i]->update_data != NULL)
                {
                    {
                        char c;
                        while ((c = fgetc(p_in)) != '\n')
                            ;
                    }
                }
            }

            all = (Product**)realloc(all, (i + 2) * sizeof(Product*));

            if (count % 2 == 0)
                f2 = false;
            else f1 = false;

            if (all[i] != NULL)
                i++;

            count++;

            all[i] = (Product*)malloc(sizeof(Product));
            if (get_product(all[i], p_in) == 1)
            {
                if (count % 2 == 0)
                    f1 = true;      // между записями одна пустая строка
                else f2 = true;
            }
            all[i] = chek_null(all[i]);
        } while (f1 == true && f2 == true);  // две пустые строки конец записываемых данных
    }
    pi[0] = i;
    return all;
}