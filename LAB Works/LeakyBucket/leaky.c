#include <stdio.h>
#include <stdlib.h>

// Define a struct for a packet with a time and a size.
struct packet
{
  int time; // Arrival time of the packet.
  int size; // Size of the packet.
} p[50];    // Array to hold up to 50 packets.

int main()
{
  int i, m, n, k = 0;
  int bsize, bfilled, outrate;

  // Prompt the user for the number of packets.
  printf("Enter the number of packets:");
  scanf("%d", &n);

  // Prompt the user to enter details for each packet in order of their arrival time.
  printf("Enter packets in the order of their arrival time\n");

  for (i = 0; i < n; i++)
  {
    printf("Enter the time and size:");
    scanf("%d%d", &p[i].time, &p[i].size);
  }

  // Read bucket size from the user.
  printf("Enter the bucket size:");
  scanf("%d", &bsize);

  // Read the output rate from the user.
  printf("Enter the output rate:");
  scanf("%d", &outrate);

  // m holds the time of the last packet arrival.
  m = p[n - 1].time;
  i = 1;       // Initialize time counter.
  k = 0;       // Initialize packet index.
  bfilled = 0; // Bucket initially empty.

  // Continue the simulation until time exceeds the last packet arrival or bucket becomes empty.
  while (i <= m || bfilled != 0)
  {
    printf("\n\n At time %d", i);

    // If a packet arrives at the current time.
    if (p[k].time == i)
    {
      // Check if the bucket has enough space to accommodate the packet.
      if (bsize >= bfilled + p[k].size)
      {
        bfilled = bfilled + p[k].size; // Insert the packet into the bucket.
        printf("\n %dbyte packet is inserted", p[k].size);
        k = k + 1; // Move to the next packet.
      }
      else
      {
        // If the bucket does not have space, discard the packet.
        printf("\n %dbyte packet is discarded", p[k].size);
        k = k + 1; // Move to the next packet.
      }
    }

    // Transmit packets from the bucket based on the output rate.
    if (bfilled == 0)
    {
      printf("\n No packets to transmit");
    }
    else if (bfilled >= outrate)
    {
      bfilled = bfilled - outrate; // Transmit 'outrate' bytes.
      printf("\n%dbytes transferred", outrate);
    }
    else
    {
      // If bucket contains less than 'outrate', transmit all bytes.
      printf("\n%dbytes transferred", bfilled);
      bfilled = 0; // Empty the bucket.
    }

    // Display the remaining bytes in the bucket.
    printf("\nPackets in the bucket %dbyte", bfilled);
    i++; // Move to the next time unit.
  }

  return 0;
}
