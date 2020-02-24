void prefix_shm(char *a) {
  if (strlen(a) == 1 ) {
    a[1] = a[0];
    a[0] = '0';
  }
}
