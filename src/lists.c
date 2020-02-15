/*------------ -------------- -------- --- ----- ---   --       -            -
 *  libreblackjack
 *
 *  Copyright (C) 2016--2020 jeremy theler
 *
 *  This file is part of libreblackjack.
 *
 *  libreblackjack is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  libreblackjack is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with libreblackjack.  If not, see <http://www.gnu.org/licenses/>.
 *------------------- ------------  ----    --------  --     -       -         -
 */
#ifndef _LIBREBLACKJACK_H_
#include "libreblackjack.h"
#endif



#define LL_FOREACH(h,e) for(e=h;e!=NULL;e=e->next)
#define LL_FOREACH_SAFE(h,e,tmp) for(e=h;e!=NULL&&(tmp = e->next)!=NULL; e = tmp)

void
append_card (card_t ** head, card_t * card)
{

  card_t *last;
  card->next = NULL;
  if (*head != NULL)
    {
      for (last = *head; last->next != NULL; last = last->next);
      last->next = card;
    }
  else
    {
      *head = card;
    }

  return;
}

void
append_hand (hand_t ** head, hand_t * hand)
{

  hand_t *last;
  hand->next = NULL;
  if (*head != NULL)
    {
      for (last = *head; last->next != NULL; last = last->next);
      last->next = hand;
    }
  else
    {
      *head = hand;
    }

  return;
}

void
delete_card (card_t ** head, card_t * card)
{
  card_t *tmp;
  if (*head == card)
    {
      *head = (*head)->next;
    }
  else
    {
      for (tmp = *head; tmp->next && tmp->next != card; tmp = tmp->next);
      if (tmp->next)
	{
	  tmp->next = card->next;
	}
    }

  return;
}

void
delete_hand (hand_t ** head, hand_t * hand)
{
  hand_t *tmp;
  if (*head == hand)
    {
      head = &(*head)->next;
    }
  else
    {
      for (tmp = *head; tmp->next && tmp->next != hand; tmp = tmp->next);
      if (tmp->next)
	{
	  tmp->next = hand->next;
	}
    }

  return;
}
