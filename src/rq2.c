#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINELENGTH_MAX 256

static int count_numberoflines_infile(char *filename) {
    FILE *f;
    char lb[LINELENGTH_MAX];
    int lc;
    f = fopen(filename, "r");
    lc = 0;
    while((fgets(lb, LINELENGTH_MAX, f))) {
        lc++;
    }
    fclose(f);
    return lc;
}

static int fill_coveragearray_fromfile(char *filename, double *covarr, int count) {
    FILE *f;
    char buf[LINELENGTH_MAX];
    f = fopen(filename, "r");
    for(int i=0; i<count; i++) {
        fscanf(f, "%s %s %lf %s\n", buf, buf, (covarr+i), buf);
    }
    fclose(f);
    return 0;
}

static void read_coveragearray_fromfile(char *filename, double **pcovarr, int *pn) {
    int n;
    double *ca;
    n = count_numberoflines_infile(filename) - 4;
    ca = (double *)malloc((size_t)n*sizeof(double));
    fill_coveragearray_fromfile(filename, ca, n);
    *pcovarr = ca;
    *pn = n;
}

static double calculate_relativeredundancy(double *r, double *s, int n) {
    double relred = 0.0;
    for(int i=0; i<n; i++) {
        relred = relred + (s[i]-r[i])/r[i];
    }
    return relred / n;
}

static int isswitch(char *s) {
	return strcmp(s,"-r")==0 || strcmp(s,"-s")==0 || strcmp(s,"-o")==0 || strcmp(s, "-a")==0;
}

int main(int argc, char *argv[])
{
    char **rfilenames;
    int rfilecount;
    char ***sfilenamegroups;
    int *sfilecounts;
    int sfilegroupcount;

    char *outputfilename = "rr.txt";
    int print_average = 0;

    double *rarray;
    int rcount;
    double *srarray;
    int scount;
    double rr;
    double rr_avg = 0.0;

    FILE *outputfile;

    rfilenames = (char **)malloc((size_t)argc*sizeof(char *));
    rfilecount = 0;

    sfilenamegroups = (char ***)malloc((size_t)argc*sizeof(char **));
    sfilecounts = (int *)malloc((size_t)argc*sizeof(int));
    sfilegroupcount = 0;
    if(argc > 0) {
        for(int i=0; i<argc; i++) {
            if(strcmp(argv[i],"-r") == 0) {
                i++;
                while(i<argc && !isswitch(argv[i])) {
                    rfilenames[rfilecount] = argv[i];
                    rfilecount++;
                    i++;
                }
                i--;
            }
            else if(strcmp(argv[i],"-s") == 0) {
                i++;
                sfilenamegroups[sfilegroupcount] = (char **)malloc((size_t)argc*sizeof(char *));
                sfilecounts[sfilegroupcount] = 0;
                while(i<argc && !isswitch(argv[i])) {
                    sfilenamegroups[sfilegroupcount][sfilecounts[sfilegroupcount]] = argv[i];
                    sfilecounts[sfilegroupcount]++;
                    i++;
                }
                if(sfilecounts[sfilegroupcount] == 0) {
                    free(sfilenamegroups[sfilegroupcount]);
                } else {
                    sfilegroupcount++;
                }
                i--;
            }
            else if(strcmp(argv[i],"-o") == 0) {
                i++;
                if(i<argc && !isswitch(argv[i])) {
                    outputfilename = argv[i];
                    i++;
                }
                i--;
            }
            else if(strcmp(argv[i],"-a") == 0) {
                print_average = 1;
            }
        }
    }

    outputfile = fopen(outputfilename, "a");
    for(int i=0; i<sfilegroupcount; i++) {
        for(int j=0; j<sfilecounts[i]; j++) {
            fprintf(outputfile, ",%s", sfilenamegroups[i][j]);
        }
        if(print_average == 1) {
            fprintf(outputfile, ",average");
        }
    }
    fprintf(outputfile, "\n");
    for(int i=0; i<rfilecount; i++) {
        fprintf(outputfile, "%s", rfilenames[i]);
        read_coveragearray_fromfile(rfilenames[i], &rarray, &rcount);
        for(int j=0; j<sfilegroupcount; j++) {
            for(int k=0; k<sfilecounts[j]; k++) {
                read_coveragearray_fromfile(sfilenamegroups[j][k], &srarray, &scount);
                rr = calculate_relativeredundancy(rarray, srarray, scount);
                fprintf(outputfile, ",%lf", rr);
                rr_avg = rr_avg + rr;
                free(srarray);
            }
            rr_avg = rr_avg / sfilecounts[j];
            if(print_average == 1) {
                fprintf(outputfile, ",%lf", rr_avg);
            }
        }
        fprintf(outputfile, "\n");
        free(rarray);
    }
    fclose(outputfile);
    for(int i=0; i<sfilegroupcount; i++) {
        free(sfilenamegroups[i]);
    }
    free(sfilecounts);
    free(sfilenamegroups);
    free(rfilenames);

    return 0;
}
