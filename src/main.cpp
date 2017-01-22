int node1(int a) {
  return a+1;
}

int node2(int a) {
  return a / 2;
}

int main() {
  return node2(node1(3));
  
}
