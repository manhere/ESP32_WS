
void Map1code( void * pvParameters ) {
  while (1) {
    // color mode
    if (color_mode >= 0 && color_mode <= 10) {
      for (int i = 0 ; i < NUM_LEDS_PER_STRIP ; i++) {
        pi_0_r[i] = rr;
        pi_0_g[i] = gg;
        pi_0_b[i] = bb;
        pi_1_r[i] = rr;
        pi_1_g[i] = gg;
        pi_1_b[i] = bb;
        pi_2_r[i] = rr;
        pi_2_g[i] = gg;
        pi_2_b[i] = bb;
        pi_3_r[i] = rr;
        pi_3_g[i] = gg;
        pi_3_b[i] = bb;
        pi_0_sr[i] = srr;
        pi_0_sg[i] = sgg;
        pi_0_sb[i] = sbb;
        pi_1_sr[i] = srr;
        pi_1_sg[i] = sgg;
        pi_1_sb[i] = sbb;
        pi_2_sr[i] = srr;
        pi_2_sg[i] = sgg;
        pi_2_sb[i] = sbb;
        pi_3_sr[i] = srr;
        pi_3_sg[i] = sgg;
        pi_3_sb[i] = sbb;
      }
    } else if (color_mode >= 11 && color_mode <= 20) {
      if (pix_mod >= 11 && pix_mod <= 20 || pix_mod >= 31 && pix_mod <= 60 || pix_mod >= 91 && pix_mod <= 120) {
        pix_pos = (((pix_start + N_L_P_S + pix_end) * pix_pos_v) / 255) - (pix_end + 1);
      } else if (pix_mod >= 21 && pix_mod <= 30 || pix_mod >= 61 && pix_mod <= 90 || pix_mod >= 121 && pix_mod <= 150) {
        pix_pos = (((pix_start + numberOfLed + pix_end) * pix_pos_v) / 255) - (pix_end + 1);
      } else {
        pix_pos = (((pix_start + N_L_P_S + pix_end) * pix_pos_v) / 255) - (pix_end + 1);
      }
      float P_S = srr;
      float P_E = sgg;
      float P_S_E;
      float P_S_N;

      for (int i = 0 ; i < NUM_LEDS_PER_STRIP ; i++) {
        if (P_S < P_E) {
          P_S_E = P_E - P_S;
        } else if (P_S > P_E) {
          P_S_E = P_S - P_E;
        } else if (P_S == P_E) {
          P_S_E = P_S;
        }
        P_S_N = P_S + ((P_S_E / NUM_LEDS_PER_STRIP ) * i);

        if (P_S_N >= 0 && P_S_N < 42.5) {
          rrr = map(P_S_N, 0, 42.5, 255, 255);
          ggg = map(P_S_N, 0, 42.5, 0, 255);
          bbb = map(P_S_N, 0, 42.5, 0, 0);
        } else if (P_S_N >= 42.5 && P_S_N < 85) {
          rrr = map(P_S_N, 42.5, 85, 255, 0);
          ggg = map(P_S_N, 42.5, 85, 255, 255);
          bbb = map(P_S_N, 42.5, 85, 0, 0);
        } else if (P_S_N >= 85 && P_S_N < 127.5) {
          rrr = map(P_S_N, 85, 127.5, 0, 0);
          ggg = map(P_S_N, 85, 127.5, 255, 255);
          bbb = map(P_S_N, 85, 127.5, 0, 255);
        } else if (P_S_N >= 127.5 && P_S_N < 170) {
          rrr = map(P_S_N, 127.5, 170, 0, 0);
          ggg = map(P_S_N, 127.5, 170, 255, 0);
          bbb = map(P_S_N, 127.5, 170, 255, 255);
        } else if (P_S_N >= 170 && P_S_N < 212.5) {
          rrr = map(P_S_N, 170, 212.5, 0, 255);
          ggg = map(P_S_N, 170, 212.5, 0, 0);
          bbb = map(P_S_N, 170, 212.5, 255, 255);
        } else if (P_S_N >= 212.5 && P_S_N <= 255) {
          rrr = map(P_S_N, 212.5, 255, 255, 255);
          ggg = map(P_S_N, 212.5, 255, 0, 0);
          bbb = map(P_S_N, 212.5, 255, 255, 0);
        }

        int ci = pix_pos + i - 1;
        if (ci > NUM_LEDS_PER_STRIP) {
          ci = ci - NUM_LEDS_PER_STRIP - 1;
        }

        if (ci >= 0 && ci <= N_L_P_S) {
          pi_0_r[ci] = (( rrr * rrr / 255 )  * rr) / 255;
          pi_0_g[ci] = (( ggg * ggg / 255 )  * gg) / 255;
          pi_0_b[ci] = (( bbb * bbb / 255 )  * bb) / 255;
          pi_0_sr[ci] = 0;
          pi_0_sg[ci] = 0;
          pi_0_sb[ci] = 0;
          pi_1_r[ci] = (( rrr * rrr / 255 )  * rr) / 255;
          pi_1_g[ci] = (( ggg * ggg / 255 )  * gg) / 255;
          pi_1_b[ci] = (( bbb * bbb / 255 )  * bb) / 255;
          pi_1_sr[ci] = 0;
          pi_1_sg[ci] = 0;
          pi_1_sb[ci] = 0;
          pi_2_r[ci] = (( rrr * rrr / 255 )  * rr) / 255;
          pi_2_g[ci] = (( ggg * ggg / 255 )  * gg) / 255;
          pi_2_b[ci] = (( bbb * bbb / 255 )  * bb) / 255;
          pi_2_sr[ci] = 0;
          pi_2_sg[ci] = 0;
          pi_2_sb[ci] = 0;
          pi_3_r[ci] = (( rrr * rrr / 255 )  * rr) / 255;
          pi_3_g[ci] = (( ggg * ggg / 255 )  * gg) / 255;
          pi_3_b[ci] = (( bbb * bbb / 255 )  * bb) / 255;
          pi_3_sr[ci] = 0;
          pi_3_sg[ci] = 0;
          pi_3_sb[ci] = 0;
        }
      }//for (i = 0 ; i < NUM_LEDS_PER_STRIP ; i++)
    }//(color_mode >= 11 && color_mode <= 20)




    else if (color_mode >= 21 && color_mode <= 30) {
      if (pix_mod >= 11 && pix_mod <= 20 || pix_mod >= 31 && pix_mod <= 60 || pix_mod >= 91 && pix_mod <= 120) {
        pix_pos = (((pix_start + N_L_P_S + pix_end) * pix_pos_v) / 255) - (pix_end + 1);
      } else if (pix_mod >= 21 && pix_mod <= 30 || pix_mod >= 61 && pix_mod <= 90 || pix_mod >= 121 && pix_mod <= 150) {
        pix_pos = (((pix_start + numberOfLed + pix_end) * pix_pos_v) / 255) - (pix_end + 1);
      } else {
        pix_pos = (((pix_start + N_L_P_S + pix_end) * pix_pos_v) / 255) - (pix_end + 1);
      }
      float P_S = srr;
      float P_E = sgg;
      float P_S_E;
      float P_S_N;

      for (int i = 0 ; i < numberOfLed ; i++) {
        if (P_S < P_E) {
          P_S_E = P_E - P_S;
        } else if (P_S > P_E) {
          P_S_E = P_S - P_E;
        } else if (P_S == P_E) {
          P_S_E = P_S;
        }
        P_S_N = P_S + ((P_S_E / numberOfLed ) * i);

        if (P_S_N >= 0 && P_S_N < 42.5) {
          rrr = map(P_S_N, 0, 42.5, 255, 255);
          ggg = map(P_S_N, 0, 42.5, 0, 255);
          bbb = map(P_S_N, 0, 42.5, 0, 0);
        } else if (P_S_N >= 42.5 && P_S_N < 85) {
          rrr = map(P_S_N, 42.5, 85, 255, 0);
          ggg = map(P_S_N, 42.5, 85, 255, 255);
          bbb = map(P_S_N, 42.5, 85, 0, 0);
        } else if (P_S_N >= 85 && P_S_N < 127.5) {
          rrr = map(P_S_N, 85, 127.5, 0, 0);
          ggg = map(P_S_N, 85, 127.5, 255, 255);
          bbb = map(P_S_N, 85, 127.5, 0, 255);
        } else if (P_S_N >= 127.5 && P_S_N < 170) {
          rrr = map(P_S_N, 127.5, 170, 0, 0);
          ggg = map(P_S_N, 127.5, 170, 255, 0);
          bbb = map(P_S_N, 127.5, 170, 255, 255);
        } else if (P_S_N >= 170 && P_S_N < 212.5) {
          rrr = map(P_S_N, 170, 212.5, 0, 255);
          ggg = map(P_S_N, 170, 212.5, 0, 0);
          bbb = map(P_S_N, 170, 212.5, 255, 255);
        } else if (P_S_N >= 212.5 && P_S_N <= 255) {
          rrr = map(P_S_N, 212.5, 255, 255, 255);
          ggg = map(P_S_N, 212.5, 255, 0, 0);
          bbb = map(P_S_N, 212.5, 255, 255, 0);
        }

        int ci = pix_pos + i - 1;
        if (ci > NUM_LEDS_PER_STRIP) {
          ci = ci - NUM_LEDS_PER_STRIP - 1;
        } else  if (ci > NUM_LEDS_PER_STRIP * 2) {
          ci = ci - (NUM_LEDS_PER_STRIP * 2) - 1;
        } else  if (ci > NUM_LEDS_PER_STRIP * 3) {
          ci = ci - (NUM_LEDS_PER_STRIP * 3) - 1;
        } else  if (ci > NUM_LEDS_PER_STRIP * 4) {
          ci = ci - (NUM_LEDS_PER_STRIP * 4) - 1;
        }
        if (ci >= 0 && ci <= N_L_P_S) {
          pi_0_r[ci] = (( rrr * rrr / 255 )  * rr) / 255;
          pi_0_g[ci] = (( ggg * ggg / 255 )  * gg) / 255;
          pi_0_b[ci] = (( bbb * bbb / 255 )  * bb) / 255;
          pi_0_sr[ci] = 0;
          pi_0_sg[ci] = 0;
          pi_0_sb[ci] = 0;
        } else if (ci > N_L_P_S && ci <= N_L_P_S * 2) {
          pi_1_r[ci] = (( rrr * rrr / 255 )  * rr) / 255;
          pi_1_g[ci] = (( ggg * ggg / 255 )  * gg) / 255;
          pi_1_b[ci] = (( bbb * bbb / 255 )  * bb) / 255;
          pi_1_sr[ci] = 0;
          pi_1_sg[ci] = 0;
          pi_1_sb[ci] = 0;
        } else if (ci > N_L_P_S * 2 && ci <= N_L_P_S * 3) {
          pi_2_r[ci] = (( rrr * rrr / 255 )  * rr) / 255;
          pi_2_g[ci] = (( ggg * ggg / 255 )  * gg) / 255;
          pi_2_b[ci] = (( bbb * bbb / 255 )  * bb) / 255;
          pi_2_sr[ci] = 0;
          pi_2_sg[ci] = 0;
          pi_2_sb[ci] = 0;
        } else if (ci > N_L_P_S * 3 && ci <= N_L_P_S * 4) {
          pi_3_r[ci] = (( rrr * rrr / 255 )  * rr) / 255;
          pi_3_g[ci] = (( ggg * ggg / 255 )  * gg) / 255;
          pi_3_b[ci] = (( bbb * bbb / 255 )  * bb) / 255;
          pi_3_sr[ci] = 0;
          pi_3_sg[ci] = 0;
          pi_3_sb[ci] = 0;
        }
      }//for (int i = 0 ; i < numberOfLed ; i++) {
    }//else if (color_mode >= 21 && color_mode <= 30)

  }
}
