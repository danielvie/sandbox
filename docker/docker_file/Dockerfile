FROM debian:bullseye-20240211

WORKDIR /usr/src

RUN apt-get update && \
    apt-get install -y python3 python3-pip
    
RUN useradd --create-home appuser
USER appuser

COPY app.py .

ENV API_KEY=hi_mom

EXPOSE 8000
