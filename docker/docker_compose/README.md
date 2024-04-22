


# classical docker
```bash
docker run --name web -itd -p 8080:80 nginx
```

# docker compose

when using docker-compose you'll wanna create a folder for that component

```bash
mkdir coffeetime
cd coffeetime
docker run --name web -itd -p 8080:80 nginx
```