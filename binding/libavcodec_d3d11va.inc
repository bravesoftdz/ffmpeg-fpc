//
// avcodec.h header binding for the Free Pascal Compiler aka FPC
//
// Binaries and demos available at http://www.djmaster.com/
//

(*
 * Direct3D11 HW acceleration
 *
 * copyright (c) 2009 Laurent Aimar
 * copyright (c) 2015 Steve Lhomme
 *
 * This file is part of FFmpeg.
 *
 * FFmpeg is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * FFmpeg is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with FFmpeg; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 *)

// #ifndef AVCODEC_D3D11VA_H
// #define AVCODEC_D3D11VA_H

(**
 * @file
 * @ingroup lavc_codec_hwaccel_d3d11va
 * Public libavcodec D3D11VA header.
 *)

#if !defined(_WIN32_WINNT) || _WIN32_WINNT < $0602
#undef _WIN32_WINNT
  _WIN32_WINNT = $0602;
{$endif}

#include <stdint.h>
#include <d3d11.h>

(**
 * @defgroup lavc_codec_hwaccel_d3d11va Direct3D11
 * @ingroup lavc_codec_hwaccel
 *
 * @{
 *)
const
  FF_DXVA2_WORKAROUND_SCALING_LIST_ZIGZAG = 1; ///< Work around for Direct3D11 and old UVD/UVD+ ATI video cards
  FF_DXVA2_WORKAROUND_INTEL_CLEARVIDEO = 2; ///< Work around for Direct3D11 and old Intel GPUs with ClearVideo interface

(**
 * This structure is used to provides the necessary configurations and data
 * to the Direct3D11 FFmpeg HWAccel implementation.
 *
 * The application must make it available as AVCodecContext.hwaccel_context.
 *
 * Use av_d3d11va_alloc_context() exclusively to allocate an AVD3D11VAContext.
 *)
type
  PAVD3D11VAContext = ^AVD3D11VAContext;
  AVD3D11VAContext = record
    (**
     * D3D11 decoder object
     *)
    decoder: PID3D11VideoDecoder;

    (**
      * D3D11 VideoContext
      *)
    video_context: PID3D11VideoContext;

    (**
     * D3D11 configuration used to create the decoder
     *)
    cfg: PD3D11_VIDEO_DECODER_CONFIG;

    (**
     * The number of surface in the surface array
     *)
    surface_count: cunsigned;

    (**
     * The array of Direct3D surfaces used to create the decoder
     *)
    surface: PPID3D11VideoDecoderOutputView;

    (**
     * A bit field configuring the workarounds needed for using the decoder
     *)
    workaround: cuint64_t;

    (**
     * Private to the FFmpeg AVHWAccel implementation
     *)
    report_id: cunsigned;

    (**
      * Mutex to access video_context
      *)
    context_mutex: HANDLE;
  end;

(**
 * Allocate an AVD3D11VAContext.
 *
 * @return Newly-allocated AVD3D11VAContext or NULL on failure.
 *)
function av_d3d11va_alloc_context(): PAVD3D11VAContext; cdecl; external LIB_AVCODEC;

(**
 * @}
 *)

// #endif (* AVCODEC_D3D11VA_H *)
