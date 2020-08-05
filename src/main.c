/*------------------------------------------------------------------------------
* main.c : 
*
*          Copyright (C) 2020 , All rights reserved.
*
* version : 
* history : 2020/07/05  1.0 new

*-----------------------------------------------------------------------------*/
#include <stdarg.h>
#include "rtklib.h"

#define PROGNAME    "rnx2rtkp"          /* program name */
#define MAXFILE     16                  /* max number of input files */


/* rnx2rtkp main -------------------------------------------------------------*/
int main(int argc, char** argv)
{
	prcopt_t prcopt = prcopt_default;
	solopt_t solopt = solopt_default;
	filopt_t filopt = { "", "", "", "", "", "", "", "", "", "", "", "D:\\data\\railway\\1\\result.pos.trace" };
	snrmask_t snrmask;
	gtime_t ts = { 0 }, te = { 0 };
	double tint = 0.0, mask[9] = { 40,40,40,41,41,42,42,45,45 };
	int i = 0, j = 0, n = 0, ret, nout = 0;
	char* infile[MAXFILE], * outfile = "";

	//prcopt.mode = PMODE_KINEMA;		/* positioning mode (PMODE_???) */
	//prcopt.nf = 2;					/* number of frequencies (1:L1,2:L1+L2,3:L1+L2+L3,4:L1+L2+L3+L4) */
	//prcopt.soltype = 2;				/* solution type (0:forward,1:backward,2:combined) */
	//prcopt.elmin = 0.2617993877991494;	/* elevation mask angle (rad) */
	//prcopt.dynamics = 1;			/* dynamics model (0:none,1:velociy,2:accel) */
	//prcopt.navsys = SYS_GPS | SYS_CMP | SYS_GLO;//|SYS_GAL|SYS_CMP;// | SYS_GLO;// | SYS_GAL;
	//prcopt.sateph = EPHOPT_BRDC;
	//prcopt.ionoopt = IONOOPT_BRDC;
	//prcopt.tropopt = TROPOPT_SAAS;
	//prcopt.modear = ARMODE_FIXHOLD;
	//prcopt.glomodear = 0;			//(0:off,1:on)
	//prcopt.bdsmodear = 0;			//(0:off,1:on)
	//prcopt.arfilter = 1;			/* AR filtering to reject bad sats (0:off,1:on) */
	//snrmask.ena[0] = 1;				//rover(0:off,1:on)
	//snrmask.ena[1] = 1;				//base
	//for (i = 0; i < 9; i++) {		// mask (dBHz) at 5,15,...85 deg 
	//	for (j = 0; j < NFREQ; j++)
	//		snrmask.mask[j][i] = mask[i];
	//}
	//prcopt.snrmask = snrmask;		//(0:off,1:on)/* use stdev estimates from receiver to adjust measurement variances */
	//prcopt.elmaskar = 15;			/* elevation mask of AR for rising satellite (deg) */
	//prcopt.elmaskhold = 15;			/* elevation mask to hold ambiguity (deg) */

	//prcopt.thresar[0] = 2;			// ratio /* AR validation threshold */
	//prcopt.varholdamb = 0.1;		/* variance for fix-and-hold psuedo measurements (cycle^2) */
	//prcopt.gainholdamb = 0.01;		/* gain used for GLO and SBAS sats to adjust ambiguity */
	//prcopt.minfixsats = 4;			/* min sats to fix integer ambiguities */
	//prcopt.minholdsats = 5;			/* min sats to hold integer ambiguities */
	//prcopt.mindropsats = 10;		/* min sats to drop sats in AR */
	//prcopt.rcvstds = 0;
	//prcopt.syncsol = 0;				//* solution sync mode (0:off,1:on) */
	//prcopt.thresslip = 0.05;		/* slip threshold of geometry-free phase (m) */
	//prcopt.niter = 1;				/* number of filter iteration */


	////prcopt.prn[3] = 1;			// [3]acch 1E-1->1
	////prcopt.prn[4] = 0.25;			// [4]accv 1E-2->0.25
	//prcopt.posopt[4] = 0;			// raim/* positioning options */
	//prcopt.err[4] = 10;				// 10Hz
	//prcopt.minlock = 0;				// 30s is recommended/* min lock count to fix ambiguity */
	//prcopt.eratio[0] = 300;			// L1
	//prcopt.eratio[1] = 100;			// L2
	//prcopt.eratio[2] = 1;			// eratio doppler
	//prcopt.maxinno = 5;				//* reject threshold of innovation (m) */
	//prcopt.maxgdop = 30;			/* reject threshold of gdop */

	//prcopt.refpos = 3;				/* base position for relative mode */
	//								/* (0:pos in prcopt,  1:average of single pos, */
	//								/*  2:read from file, 3:rinex header, 4:rtcm pos) */
	//prcopt.rovpos = 1;				// single /* rover position for fixed mode */
	//prcopt.baseline[0] = 0;			/* baseline length constraint {const,sigma} (m) */
	//prcopt.baseline[1] = 0;
	//prcopt.maxtdiff = 30.0;			// max difference of time(sec)


	//solopt.posf = SOLF_XYZ;			/* solution format (SOLF_???) */
	//solopt.outhead = 1;				/* output header (0:no,1:yes) */
	//solopt.outopt = 1;				/* output processing options (0:no,1:yes) */
	//solopt.outvel = 0;				/* output velocity options (0:no,1:yes) */
	//solopt.times = TIMES_GPST;		/* time system (TIMES_???) */
	//solopt.timef = 1;				/* time format (0:sssss.s,1:yyyy/mm/dd hh:mm:ss.s) */
	//solopt.degf = 0;				/* latitude/longitude format (0:ddd.ddd,1:ddd mm ss) */
	//solopt.height = 0;				/* height (0:ellipsoidal,1:geodetic) */
	//solopt.solstatic = 0;			/* solution of static mode (0:all,1:single) */
	//solopt.trace = 5;
	//solopt.sstat = 2;				// solution statistics level (0:off,1:states,2:residuals)


	const char fpconf[] = "D:\\data\\railway\\RTK_new.conf";
	loadopts(fpconf, sysopts);
	getsysopts(&prcopt,&solopt,&filopt);
	

	
	infile[n++] = "D:\\data\\railway\\1\\1_online.19O"; //rover
	//infile[n++] = "D:\\data\\railway\\1\\278.19O";		//base
	infile[n++] = "D:\\data\\railway\\1\\284.19O";		//base
	infile[n++] = "D:\\data\\railway\\brdm3040.19p";
	outfile = "D:\\data\\railway\\1\\result_284_init_cov_com.pos";

	solopt.trace = 1;
	prcopt.soltype = 2;				/* solution type (0:forward,1:backward,2:combined) */

	printf("trace file is %s\n",filopt.trace);
	ret = postpos(ts, te, tint, 0.0, &prcopt, &solopt, &filopt, infile, n, outfile, "", "");

	return 1;
}
