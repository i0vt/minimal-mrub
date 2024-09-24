#include <stdlib.h>
#include <mruby.h>
#include <mruby/data.h>
#include <mruby/class.h>
#include <mruby/compile.h>

#define SPOKO_NAZWA "Spoko"
struct Spoko_Dane
{
 uint32_t jeden[16];
 uint32_t dwa[16];
};

static const mrb_data_type Spoko_Typ =
{
 SPOKO_NAZWA, mrb_free
};

mrb_value Spoko_initialize(mrb_state* state, mrb_value self)
{
mrb_int n;

 mrb_get_args(state, "i", &n);
 struct Spoko_Dane *spo = (struct Spoko_Dane *)DATA_PTR(self);
 if(spo){ mrb_free(state, spo); }

 spo = (struct Spoko_Dane *)malloc(sizeof(struct Spoko_Dane));

 for(uint32_t i = 0; i < 16; ++i)
  {
  spo->jeden[i] = i * n;
  spo->dwa[i] = i * n * 2;
  }

 mrb_data_init(self, spo, &Spoko_Typ);

return self;
}

mrb_value Spoko_pisz(mrb_state* state, mrb_value self)
{
struct Spoko_Dane *spo;

 Data_Get_Struct(state, self, &Spoko_Typ, spo);
 mrb_assert(spo != NULL);
 for(uint32_t i = 0; i < 16; ++i)
  { printf("%d ",(uint32_t)spo->jeden[i]); }
 printf(" -- ");
 for(uint32_t i = 0; i < 16; ++i)
  { printf("%d:", (uint32_t)spo->dwa[i]); }
 printf("\n");

return mrb_nil_value();
}

char naglowek_pliku[3] = "SPO";

mrb_value Spoko_zapisz(mrb_state* state, mrb_value self)
{
struct Spoko_Dane *spo;
FILE *plik;

 Data_Get_Struct(state, self, &Spoko_Typ, spo);
 mrb_assert(spo != NULL);

 if ((plik = fopen("wynik.bin","wb")) == NULL)
  { return mrb_nil_value(); }

 fwrite(naglowek_pliku, sizeof(char), 3, plik);
 fwrite(&spo, sizeof(struct Spoko_Dane), 1, plik);
 fclose(plik);

return self;
}

int main()
{
mrb_state *mrb = mrb_open();
 if (!mrb) { printf("mruby nie działa\n"); return 1; }
 printf(" Wczytałem mruby\n");

 struct RClass *Spo = mrb_define_class(mrb, SPOKO_NAZWA, mrb->object_class);
 MRB_SET_INSTANCE_TT(Spo, MRB_TT_DATA);
 mrb_define_method(mrb, Spo, "initialize", Spoko_initialize, MRB_ARGS_REQ(1));
 mrb_define_method(mrb, Spo, "pisz", Spoko_pisz, MRB_ARGS_NONE());
 mrb_define_method(mrb, Spo, "zapisz", Spoko_zapisz, MRB_ARGS_NONE());

 mrb_load_string(mrb, "a = Spoko.new(10); a.pisz; p a.zapisz()");

 mrb_close(mrb);

return 0;
}
