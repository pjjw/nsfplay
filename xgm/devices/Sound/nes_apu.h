#ifndef _NES_APU_H_
#define _NES_APU_H_
#include "../device.h"
#include "nes_dmc.h"
#include "counter.h"

namespace xgm
{
  /** Upper half of APU **/
  class NES_APU : public ISoundChip
  {
  public:
    enum
    { OPT_UNMUTE_ON_RESET=0, OPT_PHASE_REFRESH, OPT_FREQ_LIMIT, OPT_NONLINEAR_MIXER, OPT_END };

    enum
    { SQR0_MASK = 1, SQR1_MASK = 2, };

  protected:
    int option[OPT_END];        // 各種オプション
    int mask;
    INT32 sm[2][2]; // BS stereo mix

    UINT32 gclock;
    UINT8 reg[0x20];
    INT32 out[2];
    double rate, clock;

    INT32 square_table[32];     // nonlinear mixer

    Counter pcounter[2];        // phase counter

    int duty[2];
    int volume[2];
    int freq[2];
    int sfreq[2];

    bool sweep_enable[2];
    bool sweep_mode[2];
    bool sweep_write[2];
    int sweep_div_period[2];
    int sweep_div[2];
    int sweep_amount[2];

    bool envelope_disable[2];
    bool envelope_loop[2];
    bool envelope_write[2];
    int envelope_div_period[2];
    int envelope_div[2];
    int envelope_counter[2];

    int length_counter[2];

    bool enable[2];

      // temporary irq flag solution for Deflemask
    bool frame_irq;
    bool frame_irq_enable;

    void sweep_sqr (int ch); // calculates target sweep frequency
    INT32 calc_sqr (int ch);
    TrackInfoBasic trkinfo[2];

  public:
      NES_APU ();
     ~NES_APU ();
    void Reset ();
    bool Read (UINT32 adr, UINT32 & val, UINT32 id=0);
    bool Write (UINT32 adr, UINT32 val, UINT32 id=0);
    void FrameSequence(int s);
    UINT32 Render (INT32 b[2]);
    void SetRate (double rate);
    void SetClock (double clock);
    void SetOption (int id, int b);
    void SetMask(int m){ mask = m; }
    void SetStereoMix (int trk, xgm::INT16 mixl, xgm::INT16 mixr);
    ITrackInfo *GetTrackInfo(int trk);
  };

}                               // namespace

#endif
