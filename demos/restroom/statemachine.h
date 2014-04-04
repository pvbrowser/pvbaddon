// our states
static void stStart(rlState *s);
static void stSpuelen(rlState *s);
static void stLeer(rlState *s);
static void stFuellen(rlState *s);
static void stVoll(rlState *s);

// implementation of our states
static void stStart(rlState *s)
{
  DATA *d = (DATA *) s->user;
  strcpy(d->stname,"Start");
  if(d->status_spuelung == 1)              
  {
                                           d->ind = 0;
                                           s->gotoState(stSpuelen);
  }  
  d->aktueller_wasserstand = 100;
}

static void stSpuelen(rlState *s)
{
  DATA *d = (DATA *) s->user;
  strcpy(d->stname,"Spülen");
  d->aktueller_wasserstand -= 10;
  if(d->aktueller_wasserstand <= 0)        s->gotoState(stLeer);
}

static void stLeer(rlState *s)
{
  DATA *d = (DATA *) s->user;
  strcpy(d->stname,"Leer");
  if(s->stepCounter > 10)                  s->gotoState(stFuellen);
  d->aktueller_wasserstand = 0;
}

static void stFuellen(rlState *s)
{
  DATA *d = (DATA *) s->user;
  strcpy(d->stname,"Füllen");
  if     (d->status_spuelung == 1)         s->gotoState(stSpuelen);
  else if(d->aktueller_wasserstand >= 100) s->gotoState(stVoll);
  d->aktueller_wasserstand += 1;
}

static void stVoll(rlState *s)
{
  DATA *d = (DATA *) s->user;
  strcpy(d->stname,"Voll");
  s->gotoState(stStart);
  d->aktueller_wasserstand = 100;
}


