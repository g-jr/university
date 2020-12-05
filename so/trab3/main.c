/* TRAB_3: Gerenciamento de Memoria
 * Gaspar Andrade – 133633
 * UC: Sistemas Operacionais - Prof. Bruno Kimura
 * UNIFESP – ICT
 */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LIMIT_ADDRESS 512000000 // 256MB*2 = 512MB
#define SIZE_VIRTUAL 128000 // 128KB
#define SIZE_PHYSICAL 64000 // 64KB
#define BIT_MASK 0x00000FFF
#define BIT_MASK_POS 0xFFFFF000

/* --------------------------------------------------- */
struct map_virtual {
  uint8_t flag_cache:1;
  uint8_t flag_referenciada:1;
  uint8_t flag_modificada:1;
  uint8_t flag_protecao:3;
  uint8_t flag_padding:2;
  uint16_t offset_moldura:12;
  uint16_t offset_padding:4;
  struct map_virtual *next; 
};
typedef struct map_virtual map_virtual_t;

struct page_virtual { map_virtual_t *head; struct page_virtual *next; u_int32_t page_id; };
typedef struct page_virtual page_virtual_t;

struct hash_table { page_virtual_t **head; };
typedef struct hash_table hash_table_t;
/* --------------------------------------------------- */
hash_table_t *hash = NULL;

u_int32_t get_pos_hash(uint64_t virtual_addr) { return ((virtual_addr/4)/1000 % SIZE_VIRTUAL) % SIZE_PHYSICAL; }

u_int32_t get_page_virtual(uint64_t virtual_addr) { return (virtual_addr/4)/1000 % SIZE_VIRTUAL; }

u_int16_t get_moldura_address(uint64_t virtual_addr) { return (virtual_addr & BIT_MASK); }

hash_table_t *init_hash_table() {
  hash_table_t *ret = (hash_table_t*) malloc(SIZE_PHYSICAL*sizeof(hash_table_t));
  int i;
  for (i = 0; i < SIZE_PHYSICAL; i++)
    ret[i].head = (page_virtual_t**) malloc(sizeof(page_virtual_t*));
  return ret;
}

void insert_address(uint64_t virtual_addr) {
  u_int32_t pos_page, pos_hash;
  pos_page = get_page_virtual(virtual_addr);
  pos_hash = get_pos_hash(virtual_addr);
  page_virtual_t **temp = hash[pos_hash].head;
  while (*temp) { // busca a pagina virtual do endereço
    if ((*temp)->page_id == pos_page) break;
    temp = &(*temp)->next;
  }
  if (!*temp) { // cria a página se ela não existir
    *temp = (page_virtual_t*) malloc(sizeof(page_virtual_t));
    (*temp)->page_id = pos_page;
  }
  map_virtual_t **curr;
  curr = &(*temp)->head;
  while (*curr) curr = &(*curr)->next;
  *curr = (map_virtual_t*) malloc(sizeof(map_virtual_t));
  (*curr)->offset_moldura = get_moldura_address(virtual_addr);
}

void generate_values(uint64_t high, uint64_t low, uint64_t size) {
  int i;
  uint64_t num;
  srand(time(NULL));
  for (i = 0; i < size; i++) {
    num = (rand() % (high - low + 1)) + low;
    insert_address(num);
    printf("%llu ", num);
  }
  printf("\n");
}

map_virtual_t *busca_map_virtual(uint64_t virtual_addr) {
  u_int32_t pos_hash; 
  u_int32_t pos_page;
  pos_hash = get_pos_hash(virtual_addr);
  pos_page = get_page_virtual(virtual_addr);
  page_virtual_t **curr;
  curr = hash[pos_hash].head;
  map_virtual_t *p = NULL;
  printf("posição tabela hash: [%u]\n", pos_hash);
  printf("posição página virtual: [%u]\n", pos_page);
  while (*curr) { // busca a pagina da tabela fisica
    if ((*curr)->page_id == pos_page) {
      p = (*curr)->head;
      break;
    }
    curr = &(*curr)->next;
  }
  while (p) {
    if (p->offset_moldura == get_moldura_address(virtual_addr))
      return p;
    p = p->next;
  }
  return NULL;
}

int main(void) {
  hash = init_hash_table();
  uint8_t op;
  uint64_t address_id;
  printf("escolha uma opcao\n");
  printf("1:\tgerar enderecos aleatorios\n");
  printf("2:\tinserir enderecos manualmente\n");
  printf("outro:\tsair\n");
  scanf("%hhu", &op);
  if (op == 1) {
    printf("entre com a quantidade de endereços\n");
    uint64_t input_size;
    scanf("%llu", &input_size);
    uint64_t low_range, high_range;
    printf("entre com a faixa maxima de endereço\n");
    scanf("%llu", &high_range);
    printf("entre com a faixa minima de endereço\n");
    scanf("%llu", &low_range);
    printf("LISTA DE ENDERECOS GERADOS\n");
    generate_values(high_range, low_range, input_size);
  } else if (op == 2) {
    do {
      printf("endereço a ser inserido (-1 para sair): ");
      scanf("%llu", &address_id);
      if (address_id == -1) break;
      insert_address(address_id);
    } while (1);
  } else {
    free(hash);
    return 0;
  }
  map_virtual_t *temp;
  do {
    printf("endereço a ser pesquisado (-1 para sair): ");
    scanf("%llu", &address_id);
    if (address_id == -1) break;
    temp = busca_map_virtual(address_id);
    if (temp) {
      printf("flag_cache: %d\nflag_referenciada: %d\nflag_modificada: %d\nflag_protecao: %d\noffeset_moldura:%d\n",
              temp->flag_cache, temp->flag_referenciada, temp->flag_modificada, temp->flag_protecao, temp->offset_moldura);
    } else printf("page miss\n");
  } while (1);
  free(hash);
  return 0;
}
